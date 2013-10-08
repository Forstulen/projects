#include <iostream>
#include "UDPSocket.hpp"
#include "Game.hpp"
#include "GameHandler.hpp"
#include "Protocol.hpp"
#include "AGameObject.hpp"
#include "Conversions.hpp"

namespace Game
{
  GameHandler::GameHandler(Game& g):
    game_(g)
  {
    this->handlers_[Protocol::RT_SUB_EVENT] = &GameHandler::eventHandler;
    this->handlers_[Protocol::RT_SUB_OBJECT] = &GameHandler::allPacket;
    this->handlers_[Protocol::RT_SUB_BULLET] = &GameHandler::bulletHandler;
    this->handlers_[Protocol::RT_SUB_SCORE] = &GameHandler::allPacket;
    this->handlers_[Protocol::RT_SUB_GAMEOVER] = &GameHandler::allPacket;
    this->handlers_[Protocol::RT_SUB_LEVELOVER] = &GameHandler::allPacket;
  }

  GameHandler::~GameHandler()
  {
  }

  void GameHandler::receivePackets(float timer)
  {
    Network::UDPSocket &socket = this->game_.getUDPSocket();
    Network::Packet *packet;
    Game::tPlayerList* list = this->game_.getPlayers();
    Game::tPlayerList::iterator it = list->begin();
    tHandlers::iterator handlIt;
    struct sockaddr sock;
    struct sockaddr_in *tmp = 0, *playerSock = 0;

    if ((packet = socket.recvPacket(&sock)) == 0)
      return;
    tmp = reinterpret_cast<struct sockaddr_in*>(&sock);
    this->timestamp_ = timer;
    for (; it != list->end(); ++it)
    {
      playerSock = (*it)->getSockAddr();
      if (playerSock->sin_port == tmp->sin_port
          && playerSock->sin_addr.s_addr == tmp->sin_addr.s_addr)
        break;
    }
    if (it == list->end())
      return;
    if (packet->getType() == Protocol::RT_TYPE_GAME
        && (handlIt = this->handlers_.find(packet->getSubType())) != this->handlers_.end())
      (this->*(handlIt->second))(*packet, *it);
    delete packet;
  }

  void GameHandler::allPacket(Network::Packet const&, Player*)
  {
    std::cerr << "[GAME] Received Unknown Packet." << std::endl;
  }

  void GameHandler::bulletHandler(Network::Packet const& packet, Player* player)
  {
    Network::UDPSocket &sock = this->game_.getUDPSocket();
    Game::tPlayerList *pList = this->game_.getPlayers();
    Game::tPlayerList::iterator it = pList->begin();
    Protocol::CreationBulletData const* data = packet.getData<Protocol::CreationBulletData const*>();
    Protocol::ModificationBulletData modifData;

    modifData.data.timestamp = this->game_.getElapsedTime();
    modifData.data.id = this->game_.getCurrentId();
    modifData.data.posX = data->data.posX;
    modifData.data.posY = data->data.posY;
    modifData.data.direction = data->data.direction;
    modifData.beam = data->beam;
    modifData.localId = data->data.id;
    Network::Packet modifPack(&modifData, sizeof(Protocol::ModificationBulletData),
			      Protocol::RT_TYPE_GAME,
			      Protocol::RT_TT_MODIFICATION,
			      Protocol::RT_SUB_BULLET);
    sock.sendPacket(modifPack, reinterpret_cast<struct sockaddr*>(player->getSockAddr()));

    Protocol::CreationBulletData creatData;

    creatData.data.timestamp = this->game_.getElapsedTime();
    creatData.data.id = this->game_.getCurrentId();
    creatData.data.posX = data->data.posX;
    creatData.data.posY = data->data.posY;
    creatData.data.direction = data->data.direction;
    creatData.beam = data->beam;
    Conversions::fillArray(creatData.filename, data->filename, 100);
    Network::Packet creatPack(&creatData, sizeof(Protocol::CreationBulletData),
			      Protocol::RT_TYPE_GAME,
			      Protocol::RT_TT_CREATION,
			      Protocol::RT_SUB_BULLET);
    for (; it != pList->end(); ++it)
      {
	if (*it == player)
	  continue;
	sock.sendPacket(creatPack, reinterpret_cast<struct sockaddr*>((*it)->getSockAddr()));
      }
    this->game_.createBullet(data->filename, data->beam, data->data.posX,
			     data->data.posY,
			     data->data.parentId,
			     data->data.direction,
			     Asset::FRIENDS);
    this->game_.incId();
  }

  void GameHandler::eventHandler(Network::Packet const& packet, Player *player)
  {
    Protocol::PlayerEvent const* pe;
    if (packet.getTransactionType() != Protocol::RT_TT_MODIFICATION)
      return;
    pe = packet.getData<Protocol::PlayerEvent const*>();
    if (pe->id != player->getColor())
      return;
    Game::tAliveObjects &objects = this->game_.getAliveObjects();
    if (objects.find(pe->id) != objects.end())
    {
      objects[pe->id]->setPosX(pe->x);
      objects[pe->id]->setPosY(pe->y);
      objects[pe->id]->setCurrentEvent(pe->event);
    }
    Game::tPlayerList *pList = this->game_.getPlayers();
    Game::tPlayerList::iterator it = pList->begin();
    Network::UDPSocket &sock = this->game_.getUDPSocket();
    for (; it != pList->end(); ++it)
    {
      if (*it == player
          && (pe->event == Protocol::RT_EVENT_CHARGE
            || pe->event == Protocol::RT_EVENT_SHOOT))
        continue;
      sock.sendPacket(packet, reinterpret_cast<struct sockaddr*>((*it)->getSockAddr()));
    }
  }

  void GameHandler::sendDisc(Player *player)
  {
    Game::tPlayerList *pList = this->game_.getPlayers();
    Game::tPlayerList::iterator it = pList->begin();
    unsigned int id = player->getColor();
    Network::Packet p(&id, sizeof(unsigned int),
        Protocol::RT_TYPE_CONNECTION,
        Protocol::RT_TT_ERROR,
        Protocol::RT_SUB_DISC);
    Network::UDPSocket &sock = this->game_.getUDPSocket();
    for (; it != pList->end() ; ++it)
    {
      if (*it != player)
        sock.sendPacket(p, reinterpret_cast<struct sockaddr*>((*it)->getSockAddr()));
    }
  }
}
