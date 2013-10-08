#include "Game.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "Protocol.hpp"
#include "Packet.hpp"
#include "Database.hpp"
#include "LoaderManager.hpp"
#include "UDPSocket.hpp"

namespace Game
{
  Level::Level(std::string const& level, Network::UDPSocket& socket):
    currentId_(4),
    socket_(socket)
  {
    RTDB::Table		*table = RTDB::Database::getInstance()[level];
    RTDB::Table::Rows const&rows = table->getRows();
    Asset::AGameObject *servObjects;
    float			time, posX, posY, speed;
    bool			direction;

    for(RTDB::Table::Rows::const_iterator it = rows.begin();
        it != rows.end();
        ++it)
      {
	try
	  {
	    this->insertLibraryObject(it);
	  }
	catch(...)
	  {
	    std::cerr << "Core: Missing nameSprite." << std::endl;
	  }
      }
  }

  Level::~Level()
  {
  }

  void  Level::initLevel(std::list<Player*>& players,
			std::map<unsigned int, Asset::AGameObject*>& aliveObjects)
  {
    std::list<Player*>::iterator it = players.begin();
    Asset::AGameObject	*servObjects;
    unsigned int color;

    for (; it != players.end(); ++it)
      {
	color = (*it)->getColor();
	servObjects =
	  dynamic_cast<Asset::AGameObject*>(Loader::LoaderManager::getInstance().getObject("PlayerObject1"));
	if (!servObjects)
	  {
	    std::cerr << "Error: cannot load player's ship." << std::endl;
	    return;
	  }
	if (color < 4 && color >= 0)
	  {
	    servObjects->initObject(20, 50 + color * 100,
				    Asset::AssetManager::getInstance().getAssetCollisionInformation(servObjects->getResourceName()).getWidth(),
				    Asset::AssetManager::getInstance().getAssetCollisionInformation(servObjects->getResourceName()).getHeight(),
				    Asset::AssetManager::getInstance().getAssetCollisionInformation(servObjects->getResourceName()).getStartIndex(),
				    false, NULL);
	    servObjects->setId(color);
	    aliveObjects[color] = servObjects;
	    this->sendCreation(players, servObjects, 0.0f);
	  }
      }
  }

  void  Level::setNextLevel(Level *level)
  {
    this->nextLevel_ = level;
  }

  Level *Level::getNextLevel() const
  {
    return this->nextLevel_;
  }

  void  Level::popObjects(std::map<unsigned int, Asset::AGameObject*>& aliveObjects,
			  std::list<Player*>& playerList, sf::Clock& timer, Game &g)
  {
    ObjectMap::iterator	it = this->poolObjects_.begin();
    ObjectMap::iterator	toDel;
    float elapsedTime;

    elapsedTime = timer.GetElapsedTime();
    while (it != this->poolObjects_.end())
      {
	if (it->first < elapsedTime)
	  {
	    elapsedTime = timer.GetElapsedTime();
	    aliveObjects[g.getCurrentId()] = it->second;
	    it->second->setId(g.getCurrentId());
	    it->second->initObject(it->second->getPosX(), it->second->getPosY(),
				   Asset::AssetManager::getInstance().getAssetCollisionInformation(it->second->getResourceName()).getWidth(),
				   Asset::AssetManager::getInstance().getAssetCollisionInformation(it->second->getResourceName()).getHeight(),
				   Asset::AssetManager::getInstance().getAssetCollisionInformation(it->second->getResourceName()).getStartIndex(),
				   it->second->getDirection(), NULL);
	    this->sendCreation(playerList, it->second, elapsedTime);
	    g.incId();
	    toDel = it++;
	    this->poolObjects_.erase(toDel);
	  }
	else
	  ++it;
      }
  }

  void Level::sendPacketInGame(std::list<Player*>& players, Network::Packet const & packet) const
  {
    std::list<Player*>::const_iterator it = players.begin();
    for (; it != players.end(); ++it)
      {
	if (this->socket_.sendPacket(packet, reinterpret_cast<struct sockaddr*>((*it)->getSockAddr())) == false)
	  std::cout << "[Level] Error cannot send packet in Game." << std::endl;
      }
  }

  void Level::fillObjectData(Asset::AGameObject* obj, Protocol::ObjectData &data, float timer) const
  {
    data.timestamp = timer;
    data.id = obj->getId();
    data.posX = obj->getPosX();
    data.posY = obj->getPosY();
    data.direction = obj->getDirection();
    data.vecX = obj->getDirVectorX();
    data.vecY = obj->getDirVectorY();
  }

  void Level::sendCreation(std::list<Player*>& players, Asset::AGameObject* obj,
			   float timer)
  {
    Protocol::CreationObjectData data;

    if (!obj)
      return;
    this->fillObjectData(obj, data.data, timer);
    std::string const& str = obj->getFilename();
    for (int i = 0; i < str.size(); i++)
      data.filename[i] = str[i];
    data.filename[str.size()] = '\0';
    Network::Packet packet(&data, sizeof(Protocol::CreationObjectData),
			   Protocol::RT_TYPE_GAME, Protocol::RT_TT_CREATION, Protocol::RT_SUB_OBJECT);
    this->sendPacketInGame(players, packet);
  }

  void Level::sendModification(std::list<Player*>& players, Asset::AGameObject* obj, float timer)
  {
    Protocol::ObjectData data;

    this->fillObjectData(obj, data, timer);
    Network::Packet packet(&data, sizeof(Protocol::ObjectData), Protocol::RT_TYPE_GAME,
			   Protocol::RT_TT_MODIFICATION, Protocol::RT_SUB_OBJECT);
    this->sendPacketInGame(players, packet);
  }

  void Level::sendDestruction(std::list<Player*>& players, Asset::AGameObject* obj, float timer)
  {
    Protocol::ObjectData data;

    this->fillObjectData(obj, data, timer);
    Network::Packet packet(&data, sizeof(Protocol::ObjectData), Protocol::RT_TYPE_GAME,
			   Protocol::RT_TT_DESTRUCTION, Protocol::RT_SUB_OBJECT);
    this->sendPacketInGame(players, packet);
  }

  bool Level::insertLibraryObject(RTDB::Table::Rows::const_iterator &it)
  {
    Asset::AGameObject	*servObjects;
    float			time, posX, posY, speed;
    bool			direction;

    servObjects = dynamic_cast<Asset::AGameObject*>(Loader::LoaderManager::getInstance().getObject(it->first));
    if (!servObjects)
      {
	std::cout << "ERROR LIB" << std::endl;
	return (false);
      }
    time = Conversions::convertString<float>(it->second.at(1));
    posX = Conversions::convertString<float>(it->second.at(2));
    posY = Conversions::convertString<float>(it->second.at(3));
    direction = false;
    if (Conversions::convertString<int>(it->second.at(4)) == 0)
      direction = true;
    speed = Conversions::convertString<float>(it->second.at(5));
    servObjects->initObject(posX, posY, 0, 0, 0, direction, NULL);
    this->poolObjects_.insert(std::pair<float, Asset::AGameObject*>(time, servObjects));
    return (true);
  }
}
