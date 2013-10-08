#include "GameHandle.hpp"
#include "GameClient.hpp"
#include "StateManager.hpp"

namespace App
{
  GameHandler::GameHandler(Network::UDPSocket* socket, GameClient & game, Thread::Mutex &mutex)
    :game_(game),
     socketUDP_(socket),
     lastKey_(Protocol::RT_EVENT_NONE),
		 mutex_(mutex)
  {
  }

  GameHandler::~GameHandler(void)
  {
  }

  void			GameHandler::initFunctions()
  {
    this->sockAddr_.sin_family = AF_INET;
    this->sockAddr_.sin_port = htons(CoreRTYPE::getInstance().getUDPPortServer());
    this->sockAddr_.sin_addr.s_addr = inet_addr(CoreRTYPE::getInstance().getIpServer().c_str());
    this->functions_[Protocol::RT_SUB_EVENT] = &GameHandler::handleEvent;
    this->functions_[Protocol::RT_SUB_OBJECT] = &GameHandler::handleObject;
    this->functions_[Protocol::RT_SUB_BULLET] = &GameHandler::handleBullet;
    this->functions_[Protocol::RT_SUB_SCORE] = &GameHandler::handleScore;
	this->functions_[Protocol::RT_SUB_GAMEOVER] = &GameHandler::handleGameOver;
  }

  void				GameHandler::initHandler()
  {
    this->socketUDP_ = App::CoreRTYPE::getInstance().getUDPSocket();
  }

  void			GameHandler::update(Network::Packet const& packet)
  {
    if (packet.getType() == Protocol::RT_TYPE_GAME)
    {
      if (this->functions_[packet.getSubType()])
	(this->*this->functions_[packet.getSubType()])(packet);
    }
    else if (packet.getType() == Protocol::RT_TYPE_CONNECTION)
		HUDManager::getInstance().setPlayerDisconnection(packet);
  }

  //**************************************************************************

  void			GameHandler::handleEvent(Network::Packet const &data)
  {
    this->modifyPlayerObject(data);
  }

  void			GameHandler::handleObject(Network::Packet const &data)
  {
    // Thread::ScopedLock<Thread::Mutex> scopedLock(this->mutex_);

    if (data.getTransactionType() == Protocol::RT_TT_CREATION)
      this->createGameObject(data);
    else if (data.getTransactionType() == Protocol::RT_TT_MODIFICATION)
      this->modifyGameObject(data);
    else
      this->destroyGameObject(data);
  }

  void			GameHandler::handleScore(Network::Packet const &data)
  {
    // Thread::ScopedLock<Thread::Mutex> scopedLock(this->mutex_);

    HUDManager::getInstance().updateScore(data);
  }

  void			GameHandler::handleBullet(Network::Packet const &data)
  {
    // Thread::ScopedLock<Thread::Mutex> scopedLock(this->mutex_);

    if (data.getTransactionType() == Protocol::RT_TT_CREATION)
      this->createBulletObject(data);
    else if (data.getTransactionType() == Protocol::RT_TT_MODIFICATION)
      this->modifyBulletObject(data);
    else
      this->destroyBulletObject(data);
  }

	void			GameHandler::handleGameOver(Network::Packet const &data)
	{
		std::cout << "Game Over" << std::endl;
		this->game_.setGameOver(true);
	}

  //****************************************************************************

  void	GameHandler::createGameObject(Network::Packet const &data)
  {
    const Protocol::CreationObjectData	*dataObject = data.getData<const Protocol::CreationObjectData*>();

		// Thread::ScopedLock<Thread::Mutex>(this->mutex_);
    this->game_.createGameObject(std::string(dataObject->filename), "", dataObject->data.posX, dataObject->data.posY, 
				 dataObject->data.id, dataObject->data.direction, NULL, NETWORK)->setDirVector(dataObject->data.vecX, dataObject->data.vecY);
  }

  void	GameHandler::modifyGameObject(Network::Packet const &data)
  {
    const Protocol::CreationObjectData	*dataObject = data.getData<const Protocol::CreationObjectData*>();

		// Thread::ScopedLock<Thread::Mutex>(this->mutex_);
    if (this->game_.getGameObjectMap().find(dataObject->data.id) != this->game_.getGameObjectMap().end())
      this->game_.getGameObjectMap()[dataObject->data.id]->update(data);
  }

  void	GameHandler::destroyGameObject(Network::Packet const &data)
  {
    std::map<unsigned int, Asset::AGameObject*>::iterator		it;
    const Protocol::ObjectData	*dataObject = data.getData<const Protocol::ObjectData*>();

 		// Thread::ScopedLock<Thread::Mutex>(this->mutex_);
    if ((it = this->game_.getGameObjectMap().find(dataObject->id)) != this->game_.getGameObjectMap().end())
		{
			if (it->second->getGameObjectType() == Asset::POWER_UP)
				this->game_.activatePowerUp(it->second->getPowerType());
			it->second->setDeath(true);
		}
  }

  //*******************************************************************************

  void	GameHandler::modifyPlayerObject(Network::Packet const &data)
  {
    std::map<unsigned int, Asset::AGameObject*>::iterator		it;
    const Protocol::PlayerEvent	*dataObject = data.getData<const Protocol::PlayerEvent*>();

		// Thread::ScopedLock<Thread::Mutex>(this->mutex_);
    if ((it = this->game_.getGameObjectMap().find(dataObject->id)) != this->game_.getGameObjectMap().end())
      {
	if (dataObject->event == Protocol::RT_EVENT_CHARGE)
	{
		std::string weaponLevel;
		Conversions::toString<int>(this->game_.getWeaponLevel(), weaponLevel);
		this->game_.getFirePlayerVector()[dataObject->id] = this->game_.createGameObject(std::string("BulletObject" + weaponLevel), "", 0, 0, ++this->count_, true, it->second, LOCAL);
	}
	else if (dataObject->event == Protocol::RT_EVENT_SHOOT)
	  {
	    if (this->game_.getFirePlayerVector()[dataObject->id])
	      {
		this->game_.getFirePlayerVector()[dataObject->id]->setDeath(true);
		this->game_.getFirePlayerVector()[dataObject->id] = NULL;
	      }
	  }
	else
	  {
	    this->game_.getGameObjectMap().find(dataObject->id)->second->setCurrentEvent(dataObject->event);
	    this->game_.getGameObjectMap().find(dataObject->id)->second->update(data);
	  }
      }
  }

  //*******************************************************************************

  void	GameHandler::createBulletObject(Network::Packet const &data)
  {
    const Protocol::CreationBulletData	*dataObject = data.getData<const Protocol::CreationBulletData*>();

    std::stringstream ss;
	ss << dataObject->filename;
    ss << "superiorfire";
    ss << static_cast<unsigned int>(dataObject->beam);
		// Thread::ScopedLock<Thread::Mutex>(this->mutex_);
    this->game_.createGameObject(std::string(dataObject->filename), ss.str(), dataObject->data.posX, dataObject->data.posY, 
				 dataObject->data.id, dataObject->data.direction, NULL, NETWORK)->setDirVector(dataObject->data.vecX, dataObject->data.vecY);
  }

  void	GameHandler::modifyBulletObject(Network::Packet const &data)
  {	
    std::string													filename;
    std::map<unsigned int, Asset::AGameObject*>::iterator		it;
    const Protocol::ModificationBulletData						*dataObject = data.getData<const Protocol::ModificationBulletData*>();
		
		// Thread::ScopedLock<Thread::Mutex>(this->mutex_);
    if ((it = this->game_.getBulletGameObjectMap().find(dataObject->localId)) != this->game_.getBulletGameObjectMap().end())
      {
		it->second->setDeath(true);
		filename = it->second->getFilename();
		std::stringstream ss;
		ss << filename;
		ss << "superiorfire";
		ss << static_cast<unsigned int>(dataObject->beam);
		this->game_.createGameObject(filename, ss.str(), dataObject->data.posX, dataObject->data.posY, 
				     dataObject->data.id, dataObject->data.direction, NULL, NETWORK)->setDirVector(dataObject->data.vecX, dataObject->data.vecY);
      }
  }

  void	GameHandler::destroyBulletObject(Network::Packet const &data)
  {
    this->destroyGameObject(data);
  }

  //*********************************************************************************

  void	GameHandler::sendEvent(int id, Protocol::eEvent key)
  {
    if (this->lastKey_ != key && this->game_.getGameObjectMap().find(id) != this->game_.getGameObjectMap().end())
      {
	Protocol::PlayerEvent data;

	data.timestamp = 0;
	data.id = id;
	data.x = this->game_.getGameObjectMap()[id]->getPosX();
	data.y = this->game_.getGameObjectMap()[id]->getPosY();
	data.event = key;
	this->lastKey_ = key;
	this->sendUDPPacket(Network::Packet(&data, sizeof(data), Protocol::RT_TYPE_GAME, Protocol::RT_TT_MODIFICATION, Protocol::RT_SUB_EVENT));
      }
  }

  void	GameHandler::sendFire(int id, const Asset::AGameObject& fire, const std::string & beam)
  {
    if (this->game_.getBulletGameObjectMap().find(id) != this->game_.getBulletGameObjectMap().end())
      {
	Protocol::CreationBulletData	packet;
	std::string						tmp(beam.substr(beam.size() - 1, beam.size()));

	packet.data.timestamp = 0;
	packet.data.id = id;	
	packet.data.parentId = this->game_.getPlayerId();
	packet.data.posX = fire.getPosX();
	packet.data.posY = fire.getPosY();
	packet.data.vecX = 0;
	packet.data.vecY = 0;
	packet.data.direction = true;
	packet.beam = Conversions::convertString<unsigned int>(tmp);
	Conversions::fillArray(packet.filename, fire.getFilename().c_str(), fire.getFilename().size());
	this->sendUDPPacket(Network::Packet(&packet, sizeof(Protocol::CreationBulletData), Protocol::RT_TYPE_GAME, Protocol::RT_TT_CREATION, Protocol::RT_SUB_BULLET));
      }
  }

  //*********************************************************************************

  void	GameHandler::sendUDPPacket(Network::Packet const &packet)
  {
    this->socketUDP_->sendPacket(packet, reinterpret_cast<struct sockaddr*>(&this->sockAddr_));
  }
}
