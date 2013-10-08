#include <iostream>
#include <exception>
#include <cmath>
#include <SFML/System.hpp>
#include "Game.hpp"
#include "Database.hpp"
#include "AGameObject.hpp"
#include "LoaderManager.hpp"
#include "Conversions.hpp"
#include "Sleep.hpp"

int			run_func(Game::Game* g)
{
  g->run();
  return 0;
}

namespace					Game
{
  Game::Game(unsigned int port) :
    quadTree_(4, 0, 0, 800, 480), playerList_(0), udpsock_(port), inGame_(false),
    port_(port), gameHandler_(*this), nbPlayer_(0), mapManager_(&aliveObjects_, "Map", 64, 16)
  {
		this->powerUpMap_[Asset::BEAM2] = &Game::createWeapon2;
		this->powerUpMap_[Asset::BEAM3] = &Game::createWeapon3;
		this->powerUpMap_[Asset::BEAM4] = &Game::createWeapon4;
		this->powerUpMap_[Asset::BEAM5] = &Game::createWeapon5;
		this->powerUpMap_[Asset::SPEED] = &Game::increaseSpeed;
		this->powerUpMap_[Asset::MODULE] = &Game::createModule;
    this->initMap();
    this->port_ = this->udpsock_.bindSocket();
    this->level_ = new Level("Level1", this->udpsock_);
    this->currentId_ = 4;
    if (!this->mapManager_.initFromFile("../../resource/level1.rtmap"))
      std::cerr << "Failed to load ../../resource/level1.rtmap" << std::endl;
    else
    {
      this->mapManager_.setAliveObjects(&this->aliveObjects_);
           this->mapManager_.initMap(&this->currentId_);
    }
  }

  Game::~Game()
  {}

  void			Game::popPoolObject()
  {
    tObjectMap::iterator	it = this->poolObject_.begin();
    float		elapsedTime = this->gameTimer_.GetElapsedTime();

    while (it != this->poolObject_.end() && it->first < elapsedTime)
      {
	aliveObjects_[it->second->getId()] = it->second;
	this->poolObject_.erase(it++);
      }
  }

  bool			Game::objectsBehavior(tAliveObjects::iterator & it, float time)
  {
    tAliveObjects::iterator toDel;

    if (it->second->updateStatus(800, 480))
      {
	this->level_->sendDestruction(*this->playerList_, it->second, time);
	toDel = it;
	++it;
	this->aliveObjects_.erase(toDel);	
	return (false);
      }
   else if (it->second->isFiring(time))
     {
	this->level_->sendCreation(*this->playerList_,
				   this->createBullet("BulletMonsterObject1",
						      0,
						      it->second->getPosX(),
						      it->second->getPosY(), 0.0f,
						      true, Asset::OTHER), time); 
     }
    return (true);
  }

  void			Game::updateAliveObjects(float time)
  { 
    tAliveObjects::iterator it = this->aliveObjects_.begin();

    while (it != this->aliveObjects_.end())
      {
	if (it->second->update(time))
	  Asset::AssetManager::getInstance().
	    getAssetCollisionInformation(it->second->getResourceName()).
	    getNextItems(it->second->getCurrentRectToSet(),
			 it->second->getDirectionToSet());
	if (this->objectsBehavior(it, time))
	  ++it;
      }
  }

  void			Game::sendGameOver()
  {
    Network::Packet packet("", 0, Protocol::RT_TYPE_GAME,
			   Protocol::RT_TT_DESTRUCTION, Protocol::RT_SUB_GAMEOVER);
    if (this->playerList_)
      this->level_->sendPacketInGame(*this->playerList_, packet);
  }

  void			Game::run()
  {
    float		time;

    std::cout << "Game launched !" << std::endl;
    this->inGame_ = true;
    this->level_->initLevel(*this->playerList_, this->aliveObjects_);
    this->nbPlayer_ = this->playerList_->size();
    this->loopTimer_.Reset();
    this->gameTimer_.Reset();
    while (this->inGame_)
      {
        this->eraseDiscPlayers();
	this->gameHandler_.receivePackets(this->gameTimer_.GetElapsedTime());
	this->level_->popObjects(this->aliveObjects_, *this->playerList_, this->gameTimer_, *this);
        this->mapManager_.update(&this->currentId_);
	time = this->loopTimer_.GetElapsedTime();
	this->updateAliveObjects(time);
	this->loopTimer_.Reset();
	this->killingSpree();
	this->inGame_ = (this->nbPlayer_ != 0);
	if (this->nbPlayer_)
	  this->inGame_ = (this->playerList_->size() != 0);
	Tools::sleepLoop(10);
      }
    this->sendGameOver();
    this->playerList_->clear();
  }

  void			Game::start(std::list<Player*> *list)
  {
    this->playerList_ = list;
    this->thread_ = new Thread::Thread(run_func, this);
  }

  /********************************************************************************/

  bool			Game::getInGame() const
  {
    return (this->inGame_);
  }

  unsigned int		Game::getPort() const
  {
    return this->port_;
  }

  /********************************************************************************/

  void			Game::incId()
  {
    ++this->currentId_;
    if (!this->currentId_)
      this->currentId_ = 4;
  }

  void			Game::initMap()
  {
  }

  /********************************************************************************/

	void				Game::popPowerUp(Asset::AGameObject *obj)
	{
		Asset::AGameObject *powerup;
		if (this->powerUpMap_[obj->getPowerType()])
			powerup = (this->*(this->powerUpMap_[obj->getPowerType()]))();
		if (powerup)
		{
			powerup->initObject(obj->getPosX(), obj->getPosY(),
				Asset::AssetManager::getInstance().getAssetCollisionInformation(powerup->getResourceName()).getWidth(),
				Asset::AssetManager::getInstance().getAssetCollisionInformation(powerup->getResourceName()).getHeight(),
				Asset::AssetManager::getInstance().getAssetCollisionInformation(powerup->getResourceName()).getStartIndex(),
				powerup->getDirection(), NULL);
			powerup->setId(this->getCurrentId());
			this->aliveObjects_[this->getCurrentId()] = powerup;
			this->level_->sendCreation(*this->playerList_, powerup, this->gameTimer_.GetElapsedTime());
			this->incId();
		}
		else
			std::cerr << "error loading powerup" << std::endl;
	}

  void			Game::sendNewScore(tAliveObjects::iterator const & itPl, int const score)
  {    
    Protocol::ScoringData data;

    itPl->second->addScore(score);
    data.id = itPl->second->getId();
    data.score = itPl->second->getScore();
    Network::Packet packet(&data, sizeof(data), Protocol::RT_TYPE_GAME,
			   Protocol::RT_TT_MODIFICATION, Protocol::RT_SUB_SCORE);
    if (this->playerList_)
      this->level_->sendPacketInGame(*this->playerList_, packet);
  }

  void			Game::recordScore(std::pair<int, int> const & pair)
  {
    tAliveObjects::iterator it1 = this->aliveObjects_.find(pair.first);
    tAliveObjects::iterator it2 = this->aliveObjects_.find(pair.second);
    tAliveObjects::iterator itPl;

    if (it1 != this->aliveObjects_.end() && it2 != this->aliveObjects_.end())
      {
	if (it1->second->getGameObjectType() == Asset::BULLET &&
	    it2->second->getGameObjectType() == Asset::MONSTER &&
	    (itPl = this->aliveObjects_.find(it1->second->getParentId()))
	    != this->aliveObjects_.end())
	  this->sendNewScore(itPl, it2->second->getScore());
	else if (it2->second->getGameObjectType() == Asset::BULLET &&
		 it1->second->getGameObjectType() == Asset::MONSTER &&
		 (itPl = this->aliveObjects_.find(it2->second->getParentId()))
		 != this->aliveObjects_.end())
	  this->sendNewScore(itPl, it1->second->getScore());
      }
  }

  void			Game::killGameObject(int fd)
  {
    tAliveObjects::iterator	it = this->aliveObjects_.find(fd);
    float			timer = 0.0;
 
    if (it != this->aliveObjects_.end() && it->second->getGameObjectType() != Asset::WALL)
      {
	timer = this->gameTimer_.GetElapsedTime();
	if (it->second->getId() >= 0 &&
	    it->second->getId() <= 3)
	  this->nbPlayer_ -= 1;
	this->level_->sendDestruction(*this->playerList_, it->second, timer);  
	if (it->second->getResourceName().compare("monsterpowerup") == 0)
	  this->popPowerUp(it->second);
	this->aliveObjects_.erase(fd);
      }
  }

  void		Game::makeAlive(tAliveObjects::iterator &it)
  {
    if (it != this->aliveObjects_.end())
      (*it).second->setDeath(false);
  }

  bool			Game::tookBonuses(tAliveObjects::iterator &it1,
					  tAliveObjects::iterator &it2)
  {
    if (it1 != this->aliveObjects_.end() &&
	it2 != this->aliveObjects_.end())
      {
	if (it1->second->getGameObjectType() == Asset::POWER_UP
	    && it2->second->getGameObjectType() == Asset::PLAYER)
	  {
	    this->killGameObject(it1->second->getId());
	    return (true);
	  }
	else if (it2->second->getGameObjectType() == Asset::POWER_UP
		 && it1->second->getGameObjectType() == Asset::PLAYER)
	  {
	    this->killGameObject(it2->second->getId());
	    return (true);
	  }
      }
    return (false);
  }

  void			Game::killingSpree()
  {
    std::list<std::pair<unsigned int, unsigned int> > *deadLine = this->quadTree_.listingOnCollisionObject(this->aliveObjects_);
    tAliveObjects::iterator	it1;
    tAliveObjects::iterator	it2;

    if (deadLine)
      {
	for (std::list<std::pair<unsigned int, unsigned int> >::iterator it = deadLine->begin();
	     it != deadLine->end(); ++it)
	  {
	    this->recordScore(*it);
	    it2 = this->aliveObjects_.find((*it).second);
	    it1 = this->aliveObjects_.find((*it).first);
	    this->makeAlive(it2);
	    this->makeAlive(it1);	    
	    if (!this->tookBonuses(it1, it2))
	      {
		this->killGameObject((*it).first);
		this->killGameObject((*it).second);
	      }
	  }
	delete deadLine;
      }
  }

  Game::tAliveObjects& Game::getAliveObjects()
  {
    return this->aliveObjects_;
  }

  Game::tPlayerList* Game::getPlayers()
  {
    return this->playerList_;
  }

  Network::UDPSocket &Game::getUDPSocket()
  {
    return this->udpsock_;
  }

  Asset::AGameObject *Game::createBullet(std::string const& filename, unsigned char beam, float
					 posX, float posY, int parentId, bool direction,
					 Asset::eGroupObject group)
  {
    Asset::AGameObject*					object = NULL;

    if (!(object = Loader::LoaderManager::getInstance().getObject(filename)))
      return 0;
    if (object->getGroup() == Asset::FRIENDS)
    {
			std::stringstream ss; 
			ss << filename;
	    ss << "superiorfire";
	    ss << static_cast<unsigned int>(beam);
			object->setResourceName(ss.str());
    }
    object->initObject(posX, posY,
		       Asset::AssetManager::getInstance().getAssetCollisionInformation(object->getResourceName()).getWidth(),
		       Asset::AssetManager::getInstance().getAssetCollisionInformation(object->getResourceName()).getHeight(),
		       Asset::AssetManager::getInstance().getAssetCollisionInformation(object->getResourceName()).getStartIndex(),
		       direction, 0);
    object->update(0.0f);
    object->setGroup(group);
    object->setId(this->currentId_);
    object->setParentId(parentId);
    this->aliveObjects_[this->currentId_] = object;
    this->incId();
    if (object->getGameObjectType() != Asset::PLAYER && this->incNextTarget())
      {
	float   x;
	float   y;
	float dist;

	x = this->aliveObjects_[this->nextTarget_]->getPosX() - posX;
	y = this->aliveObjects_[this->nextTarget_]->getPosY() - posY;
	dist = sqrt(x * x + y * y);
	if (dist)
	  {
	    x /= dist;
	    y /= dist;
	  }
	object->setDirVector(x, y);
      }
    return object;
  }

  bool  Game::incNextTarget()
  {
    int i;
    tAliveObjects::iterator it;

    for (i = 0; i < 4 ; ++i)
      {
	this->nextTarget_ = (this->nextTarget_ + 1) % 4;
	if ((it = this->aliveObjects_.find(this->nextTarget_))
	    != this->aliveObjects_.end() && !it->second->getDeath())
	  break;
      }
    return !(i == 4);
  }

  unsigned int Game::getCurrentId() const
  {
    return this->currentId_;
  }

  float Game::getElapsedTime() const
  {
    return this->gameTimer_.GetElapsedTime();
  }

	Asset::AGameObject*				Game::createWeapon2()
	{
		Asset::AGameObject* obj;
		if ((obj = Loader::LoaderManager::getInstance().getObject("PowerUpObjectBeam2")))
			{
				obj->setPowerType(Asset::BEAM2);
				obj->setResourceName("powerupblue");
			}
		return obj;
	}

	Asset::AGameObject*				Game::createWeapon3()
	{
		return 0;
	}

	Asset::AGameObject*				Game::createWeapon4()
	{
		return 0;
	}

	Asset::AGameObject*				Game::createWeapon5()
	{
		return 0;
	}

	Asset::AGameObject*				Game::increaseSpeed()
	{
		Asset::AGameObject* obj;
			if ((obj = Loader::LoaderManager::getInstance().getObject("PowerUpObjectSpeed")))
			{
				obj->setPowerType(Asset::SPEED);
				obj->setResourceName("powerupspeed");
			}
			return obj;
	}

	Asset::AGameObject*				Game::createModule()
	{
		return 0;
	}

    void  Game::eraseDiscPlayers()
    {
      tPlayerList::iterator it = this->playerList_->begin();
      while (it != this->playerList_->end())
      {
        if (!(*it)->isReady())
        {
          if (this->aliveObjects_.find((*it)->getColor()) != this->aliveObjects_.end())
          {
            this->level_->sendDestruction(*this->playerList_, this->aliveObjects_[(*it)->getColor()],
                this->gameTimer_.GetElapsedTime());
            this->gameHandler_.sendDisc(*it);
          }
          it = this->playerList_->erase(it);
        }
        else
          ++it;
      }
    }
};
