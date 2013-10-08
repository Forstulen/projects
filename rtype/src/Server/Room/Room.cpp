#include <string>
#include <algorithm>
#include <iostream>

#include "Room.hpp"
#include "Player.hpp"
#include "Packet.hpp"
#include "Conversions.hpp"

namespace				Room
{
  Room::Room(std::string const & roomName, unsigned int port)
    : roomName_(roomName), game_(port), readyToPlayer_(0), isInGame_(false)
  {
    this->initFunctions();
  }

  Room::~Room(){}

  Room::tPlayerContainer const &	Room::getPlayerContainer() const
  {
    return this->players_;
  }

  unsigned int				Room::nbPlayers() const
  {
    return this->players_.size();
  }

  void					Room::initFunctions()
  {
    this->functions_[Conversions::encodeToUShort(Protocol::RT_TYPE_ROOM, 
						 Protocol::RT_SUB_JOIN)]
      = &Room::joinPlayer;
    this->functions_[Conversions::encodeToUShort(Protocol::RT_TYPE_ROOM,
						 Protocol::RT_SUB_READY)]
      = &Room::readyPlayer;
    this->functions_[Conversions::encodeToUShort(Protocol::RT_TYPE_ROOM,
						 Protocol::RT_SUB_PLAYERS)]
      = &Room::listPlayers;
    this->functions_[Conversions::encodeToUShort(Protocol::RT_TYPE_ROOM,
						 Protocol::RT_SUB_INFO)]
      = &Room::setUDPPlayer;
    this->functions_[Conversions::encodeToUShort(Protocol::RT_TYPE_ROOM,
						 Protocol::RT_SUB_START)]
      = &Room::startGame;
  }

  bool					Room::handlePacket(Game::Player *player, Network::Packet *packet)
  {
    unsigned short			opcode;
    tFunctionContainer::iterator	itFunct;

    opcode = Conversions::encodeToUShort(packet->getType(), packet->getSubType());
    if ((itFunct = this->functions_.find(opcode)) != this->functions_.end())
      {
	RMemFn funct = (*itFunct).second;
	return (this->*funct)(player, packet);
      }
    return false;
  }

  bool					Room::joinPlayer(Game::Player *player, Network::Packet *packet)
  {
    char const *			data(packet->getData<char const *>());
    std::string				roomName(data);
    Network::Packet *			toSend = new Network::Packet("", 0,
								     Protocol::RT_TYPE_ROOM,
								     Protocol::RT_TT_ERROR,
								     Protocol::RT_SUB_JOIN);
    delete packet;
    
    if (this->isInGame_ == true)
      {
	std::string const		error("Game already started in this room.");
	toSend->setData<char const *>(error.c_str(), error.size());
	player->pushPacket(toSend);
	return false;
      }
    else if (this->nbPlayers() >= MAXPLAYER)
      {
	std::string const		error("Too many players in the room.");
	toSend->setData<char const *>(error.c_str(), error.size());
	player->pushPacket(toSend);
	return false;
      }
    else
      {
	this->players_.push_back(player);
	toSend->setTransactionType(Protocol::RT_TT_ACK);
	player->setRoom(roomName);
	player->pushPacket(toSend);
	tPlayerContainer::iterator	itPlayer = this->players_.begin();
	for (; itPlayer != this->players_.end(); ++itPlayer)
	  this->listPlayers((*itPlayer), NULL);
	return true;
      }
    std::string const		error("Error joining the room.");
    toSend->setData<char const *>(error.c_str(), error.size());
    player->pushPacket(toSend);
    return false;
  }

  bool					Room::readyPlayer(Game::Player *player, Network::Packet *packet)
  {
    tPlayerContainer::iterator		itPlayer;
    Network::Packet *			toSend;
    tPlayerContainer::iterator		itSend = this->players_.begin();
    Protocol::PlayerStatus		pState;

    delete packet;
    if ((itPlayer = std::find(this->players_.begin(), this->players_.end(), player)) != this->players_.end())
      {
	if (player->isReady() == true)
	  (*itPlayer)->setReady(false);
	else
	  (*itPlayer)->setReady(true);
	int i = 0;
	for (; i < (*itPlayer)->getId().size(); i++)
	  pState.login[i] = (*itPlayer)->getId()[i];
	pState.login[i] = '\0';
	pState.isReady = player->isReady();
	for (itSend = this->players_.begin(); itSend != this->players_.end(); ++itSend)
	  {
	    packet = new Network::Packet(&pState, sizeof(Protocol::PlayerStatus),
					 Protocol::RT_TYPE_ROOM,
					 Protocol::RT_TT_REPLY,
					 Protocol::RT_SUB_READY);
	    (*itSend)->pushPacket(packet);
	  }
	if (this->isRoomReady())
	  {
	    this->infoPlayer();
	    return true;
	  }
      }
    return false;
  }
    
  bool				Room::listPlayers(Game::Player *player, Network::Packet *packet)
  {
    tPlayerContainer::iterator	itPlayer = this->players_.begin();
    std::string			listPlayers;
    
    for (; itPlayer != this->players_.end(); ++itPlayer)
      {
	listPlayers.append((*itPlayer)->getId());
	listPlayers.append(1, '\0');
      }
    
    Network::Packet *		 toSend = new Network::Packet(listPlayers.c_str(),
							      listPlayers.size(),
							      Protocol::RT_TYPE_ROOM,
							      Protocol::RT_TT_REPLY,
							      Protocol::RT_SUB_PLAYERS);
    player->pushPacket(toSend);
    delete packet;
    return true;
  }
  
  std::string const &		Room::getName() const
  {
    return this->roomName_;
  }

  bool				Room::delPlayer(Game::Player *player)
  {
    tPlayerContainer::iterator	itPlayer;

    itPlayer = std::find(this->players_.begin(), this->players_.end(), player);
    if (itPlayer != this->players_.end())
      {
	player->setReady(false);
	player->setRoom("");
        if (this->game_.getInGame())
          return true;
	this->players_.erase(itPlayer);
	tPlayerContainer::iterator	itSend = this->players_.begin();
	for (; itSend != this->players_.end(); ++itSend)
	  this->listPlayers((*itSend), NULL);
	return true;
      }
    return false;
  }

  bool				Room::isRoomReady()
  {
    tPlayerContainer::iterator	itPlayer = this->players_.begin();
    unsigned int		nbReady = 0;

    for (; itPlayer != this->players_.end(); ++itPlayer)
      {
	if ((*itPlayer)->isReady())
	  nbReady++;
      }
    if (nbReady == this->nbPlayers())
      return true;
    else
      return false;
  }

  bool				Room::infoPlayer()
  {
    tPlayerContainer::iterator	itPlayer = this->players_.begin();
    tPlayerContainer::iterator  itSend;
    unsigned int		id = 0;
    
    Network::Packet		*packet;
    Protocol::PlayerInfo	info;
    
    for (; itPlayer != this->players_.end(); ++itPlayer)
      {
	int i = 0;
	for (; i < (*itPlayer)->getId().size(); i++)
	  info.login[i] = (*itPlayer)->getId()[i];
	info.login[i] = '\0';
	info.port = this->game_.getPort();
	info.id = id;
	(*itPlayer)->setColor(id);
	for (itSend = this->players_.begin(); itSend != this->players_.end(); ++itSend)
	  {
	    packet = new Network::Packet(&info, sizeof(Protocol::PlayerInfo),
					 Protocol::RT_TYPE_ROOM,
					 Protocol::RT_TT_REPLY,
					 Protocol::RT_SUB_INFO);
	    (*itSend)->pushPacket(packet);
	  }
	id++;
      }
    return true;
  }

  bool				Room::setUDPPlayer(Game::Player *player, Network::Packet *packet)
  {
    Protocol::PlayerInfo const 	*info;

    info = packet->getData<Protocol::PlayerInfo const *>();
    std::cout << "Port UDP Player: " << info->port << std::endl;
    player->setUDPPort(info->port);
    return true;
  }

  bool				Room::startGame(Game::Player *player, Network::Packet *packet)
  {
    Network::Packet		*toSend;

    this->readyToPlayer_++;
    if (this->players_.size() == this->readyToPlayer_)
      {
	tPlayerContainer::iterator itPlayer = this->players_.begin();

	for (; itPlayer != this->players_.end(); ++itPlayer)
	  {
	    toSend = new Network::Packet("", 0,
					 Protocol::RT_TYPE_ROOM,
					 Protocol::RT_TT_REPLY,
					 Protocol::RT_SUB_START);
	    (*itPlayer)->pushPacket(toSend);
	  }
	this->game_.start(&this->players_);
	this->isInGame_ = true;
	return true;
      }
    return false;
  }
}
