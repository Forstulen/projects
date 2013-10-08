#include <algorithm>
#include <SFML/Graphics.hpp>
#include "AState.hpp"
#include "GameClient.hpp"
#include "StarFieldManager.hpp"
#include "CoreRTYPE.hpp"
#include "Exception.hpp"
#include "AssetManager.hpp"
#include "Protocol.hpp"
#include "Conversions.hpp"
#include "HUDManager.hpp"
#include "Sound/SoundManager.hpp"
#include "StateManager.hpp"

namespace App
{
  GameClient::GameClient(Network::UDPSocket *socketUDP)
    :handler_(socketUDP, *this, this->mutex_),
     player_(NULL),
     timer_(0),
    currentMapId_(4),
    firePlayerVector_(4),
     beamValue_(0),
     isBeam_(false),
	 gameOver_(false),
     count_(4),
     mapManager_(&mapObjects_, "Map", 64, 16),
	 weaponLevel_(1),
	 speedLevel_(1)
  {

	this->powerUpMap_[Asset::BEAM2] = &GameClient::initialiseWeapon2;
	this->powerUpMap_[Asset::BEAM3] = &GameClient::initialiseWeapon3;
	this->powerUpMap_[Asset::BEAM4] = &GameClient::initialiseWeapon4;
	this->powerUpMap_[Asset::BEAM5] = &GameClient::initialiseWeapon5;
	this->powerUpMap_[Asset::SPEED] = &GameClient::increaseSpeed;
	this->powerUpMap_[Asset::MODULE] = &GameClient::initialiseModule;

	this->beamLevelMap_[0.2f] = new std::string("superiorfire0");
   this->beamLevelMap_[0.4f] = new std::string("superiorfire1");
   this->beamLevelMap_[0.6f] = new std::string("superiorfire2");
    this->beamLevelMap_[0.8f] = new std::string("superiorfire3");
    this->beamLevelMap_[1.2f] = new std::string("superiorfire4");
    this->beamLevelMap_[1.5f] = new std::string("superiorfire5");

    this->colorShipVector_.push_back("blueship");
    this->colorShipVector_.push_back("redship");
    this->colorShipVector_.push_back("yellowship");
    this->colorShipVector_.push_back("greenship");	
    fill(this->firePlayerVector_.begin(),
        this->firePlayerVector_.end(),
        static_cast<Asset::AGameObject*>(0));
  }

  GameClient::~GameClient()
  {
    for (std::map<unsigned int, Asset::AGameObject*>::iterator it = this->bulletGameObjectMap_.begin(); it != this->bulletGameObjectMap_.end(); ++it)
      delete it->second;
    for (std::map<unsigned int, Asset::AGameObject*>::iterator it = this->gameObjectMap_.begin(); it != this->gameObjectMap_.end(); ++it)
      delete it->second;
	for (std::map<unsigned int, Asset::AGameObject*>::iterator it = this->mapObjects_.begin(); it != this->mapObjects_.end(); ++it)
      delete it->second;
  }

  void						GameClient::initialize()
  {
    this->socketTCP_ = App::CoreRTYPE::getInstance().getTCPSocket();
    this->playerId_ = App::CoreRTYPE::getInstance().getPlayerId();
    this->handler_.initFunctions();
    this->handler_.initHandler();
    Sound::SoundManager::getInstance().initMusic("rtype_theme");
    this->socketTCP_->sendPacket(Network::Packet("", 0,
          Protocol::RT_TYPE_ROOM,
          Protocol::RT_TT_REQUEST,
          Protocol::RT_SUB_START), 0);
	for (std::map<unsigned int, Asset::AGameObject*>::iterator it = this->mapObjects_.begin(); it != this->mapObjects_.end(); ++it)
      delete it->second;
	this->mapObjects_.clear();
    if (!this->mapManager_.initFromFile("../../resource/level1.rtmap"))
      std::cerr << "Failed to load ../../resource/level1.rtmap" << std::endl;
    this->mapManager_.setAliveObjects(&this->mapObjects_);
    this->mapManager_.initMap(&this->currentMapId_);
  }

  void						GameClient::resetGame()
  {
    for (std::map<unsigned int, Asset::AGameObject*>::iterator it = this->bulletGameObjectMap_.begin(); it != this->bulletGameObjectMap_.end(); ++it)
      delete it->second;
    this->bulletGameObjectMap_.clear();
    for (std::map<unsigned int, Asset::AGameObject*>::iterator it = this->gameObjectMap_.begin(); it != this->gameObjectMap_.end(); ++it)
      delete it->second;
    this->gameObjectMap_.clear();
    for (std::vector<Asset::AGameObject*>::iterator it = this->firePlayerVector_.begin(); it != this->firePlayerVector_.end(); ++it)
    {
      if (*it = static_cast<Asset::AGameObject*>(0))
        delete *it;
    }
    this->player_ = NULL;
    this->timer_ = 0;
    this->isBeam_ = false;
	this->gameOver_ = false;
	this->weaponLevel_ = 1;
	this->speedLevel_ = 1;
    Sound::SoundManager::getInstance().initMusic("Starcraft");
    HUDManager::getInstance().resetHUD();
  }

  void	GameClient::draw(sf::RenderWindow* window)
  {
    StarFieldManager::getInstance().draw(window);
    HUDManager::getInstance().draw(window);
    Thread::ScopedLock<Thread::Mutex> scopedLock(this->mutex_);
    this->drawMap<unsigned int>(window, this->mapObjects_);
    this->drawMap<unsigned int>(window, this->gameObjectMap_);
    this->drawMap<unsigned int>(window, this->bulletGameObjectMap_);
  }

  void	GameClient::onPressedKey(sf::Event keyEvent)
  {
    if (keyEvent.Type == sf::Event::KeyPressed)
      if (keyEvent.Key.Code == sf::Key::Escape)
	{
		this->gameOver();
	}
  }

  void	GameClient::update(Network::Packet const& packet)
  {
    this->handler_.update(packet);
  }

  void  GameClient::update(float time)
  {
	if (this->gameOver_)
		this->gameOver();
    this->timer_ += time;
    StarFieldManager::getInstance().update(time);
    Thread::ScopedLock<Thread::Mutex> scopedLock(this->mutex_);
    this->updateMap<unsigned int>(time, this->mapObjects_);
    this->updateMap<unsigned int>(time, this->bulletGameObjectMap_);
    this->updateMap<unsigned int>(time, this->gameObjectMap_);
    this->mapManager_.update(&this->currentMapId_);
    HUDManager::getInstance().updateBeam(this->manageBullet(time));
  }

  void	GameClient::activateCheatCode()
  {

  }

  Asset::AGameObject*	GameClient::createGameObject(const std::string & name, const std::string & resource, float posX, float posY,
      unsigned int id, bool direction, const Asset::AGameObject * parent, eScope scope)
  {
    Asset::AGameObject*					object = NULL;

    if (!(object = Loader::LoaderManager::getInstance().getObject(name)))
      throw Exception("Load Assets", "Error loading " + name);
		this->initObject(object, resource, posX, posY, id, direction, parent);
    if (object->getGameObjectType() == Asset::PLAYER)
    {
      if (object->getId() != this->playerId_)
        object->setGameObjectType(Asset::FRIEND);
      else
        this->player_ = object;
    }
    if (object->getId() >= 0 && object->getId() <= 3)
      object->setResourceName(this->colorShipVector_[object->getId()]);
    if (scope == LOCAL)
      this->bulletGameObjectMap_[id] = object;
    else
      this->gameObjectMap_[id] = object;
    return object;
  }

  void	GameClient::initObject(Asset::AGameObject * object, const std::string & resource, float posX, float posY, 
      unsigned int id, bool direction, const Asset::AGameObject * parent)
  {
    if (!resource.empty())
      object->setResourceName(resource);
    object->initObject(posX, posY,
        Asset::AssetManager::getInstance().getAssetImageInformation(object->getResourceName()).getWidth(),
        Asset::AssetManager::getInstance().getAssetImageInformation(object->getResourceName()).getHeight(),
        Asset::AssetManager::getInstance().getAssetImageInformation(object->getResourceName()).getStartIndex(),
        direction, parent);
    object->setId(id);
  }

  int		GameClient::getHeight() const
  {
    return this->height_;
  }

  int		GameClient::getWidth() const
  {
    return this->width_;
  }

  int		GameClient::getPlayerId() const
  {
    return this->playerId_;
  }

  void		GameClient::setGameOver(bool value)
  {
	  this->gameOver_ = value;
  }

	bool	GameClient::getGameOver() const
	{
		return this->gameOver_;
	}

	int		GameClient::getWeaponLevel() const
	{
		return this->weaponLevel_;
	}

  void					GameClient::manageDeath(Asset::AGameObject * obj, bool explode)
  {
	  if (obj)
	  {
		if (this->player_ == obj)
		{
			this->player_ = NULL;
			Sound::SoundManager::getInstance().stopCharge();
		}
		if (obj->getId() < this->firePlayerVector_.size() && this->firePlayerVector_[obj->getId()])
		{
			this->firePlayerVector_[obj->getId()]->setDeath(true);
			this->firePlayerVector_[obj->getId()] = NULL;
		}
		if (!explode && obj->getGameObjectType() == Asset::MONSTER || obj->getGameObjectType() == Asset::PLAYER || obj->getGameObjectType() == Asset::FRIEND)
		{
			this->createGameObject("ExplosionObject1", obj->getResourceName() + "explosion", obj->getPosX(), 
									obj->getPosY(), ++this->count_, true, NULL, LOCAL);
			Sound::SoundManager::getInstance().playSound(obj->getResourceName() + "explosion");
		}
	  }
  }

  float					GameClient::manageBullet(float timer)
  {
    bool	fire = App::EventManager::getInstance().checkSpace();

    if (fire && !this->isBeam_ && this->player_)
    {
		std::string		value;
		Conversions::toString(this->weaponLevel_, value);

		this->firePlayerVector_[this->playerId_] = this->createGameObject(std::string("BulletObject" + value), "", 0, 0, this->count_, true, this->player_, LOCAL);
      Sound::SoundManager::getInstance().playCharge("charge");
      this->handler_.sendEvent(this->playerId_, Protocol::RT_EVENT_CHARGE);
      this->isBeam_ = true;
      this->beamValue_ = 0.0f;
      ++this->count_;
    }
    else if (this->isBeam_)
    {
      if (!fire && this->player_)
      {
		std::string		value;
		Conversions::toString(this->weaponLevel_, value);

        this->beamValue_ += timer;
        Sound::SoundManager::getInstance().stopCharge();
        Sound::SoundManager::getInstance().playSound(this->getBeamLevel(this->beamValue_));
        this->firePlayerVector_[this->playerId_]->update(0.0f);
		this->initObject(this->firePlayerVector_[this->playerId_], "BulletObject" + value + this->getBeamLevel(this->beamValue_), 0, 0, this->firePlayerVector_[this->playerId_]->getId(), true, this->player_);
        this->handler_.sendFire(this->firePlayerVector_[this->playerId_]->getId(), *this->firePlayerVector_[this->playerId_], "BulletObject" + this->weaponLevel_ + this->getBeamLevel(this->beamValue_));
        this->handler_.sendEvent(this->playerId_, Protocol::RT_EVENT_SHOOT);
        this->isBeam_ = false;
        return this->beamValue_ = 0.0f;
      }
      this->beamValue_ += timer;
    }
    return this->beamValue_;
  }

  const std::string &	GameClient::getBeamLevel(float value) const
  {
    float				startInverval = 0.0f;
    for (std::map<float, std::string*>::const_iterator it = this->beamLevelMap_.begin(); it != this->beamLevelMap_.end(); ++it)
      {
		if (value >= startInverval && value <= it->first)
			return *it->second;
		else
			startInverval = it->first;
      }
    return *this->beamLevelMap_.at(1.5f);
  }

  std::map<unsigned int, Asset::AGameObject*>&	GameClient::getGameObjectMap()
  {
    return this->gameObjectMap_;
  }

  std::map<unsigned int, Asset::AGameObject*>&	GameClient::getBulletGameObjectMap()
  {
    return this->bulletGameObjectMap_;
  }

  std::vector<Asset::AGameObject*>&				GameClient::getFirePlayerVector()
  {
    return this->firePlayerVector_;
  }

	void				GameClient::gameOver()
	{
		std::string const &roomName = CoreRTYPE::getInstance().getRoom();
	  this->socketTCP_->sendPacket(Network::Packet(roomName.c_str(), roomName.size() + 1,
						       Protocol::RT_TYPE_ROOM,
						       Protocol::RT_TT_REQUEST,
						       Protocol::RT_SUB_LEAVE), 0);
		CoreRTYPE::getInstance().closeUDPSocket();
	  App::StateManager::getInstance().changeState(this->nextState_);
	  App::StateManager::getInstance().getCurrentState()->initialize();
	  this->resetGame();
	}

	void				GameClient::activatePowerUp(Asset::ePowerUpType powerUpType)
	{
		for (std::map<Asset::ePowerUpType, void (GameClient::*)()>::iterator it = this->powerUpMap_.begin(); it != this->powerUpMap_.end(); ++it)
		{
			if (it->first == powerUpType)
				(this->*(it->second))();
		}
	}

	void				GameClient::initialiseWeapon2()
	{
		this->weaponLevel_ = 2;
	}

	void				GameClient::initialiseWeapon3()
	{
		this->weaponLevel_ = 3;
	}

		
	void				GameClient::initialiseWeapon4()
	{
		this->weaponLevel_ = 4;
	}

	void				GameClient::initialiseWeapon5()
	{
		this->weaponLevel_ = 5;
	}

	void				GameClient::initialiseModule()
	{
		//TODO
	}

	void				GameClient::increaseSpeed()
	{
		++this->speedLevel_;
	}
}
