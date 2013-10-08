#ifndef GAMECLIENT_HPP
#define GAMECLIENT_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <vector>
#include "Packet.hpp"
#include "AState.hpp"
#include "EventManager.hpp"
#include "UDPSocket.hpp"
#include "TCPClient.hpp"
#include "AGameObject.hpp"
#include "LoaderManager.hpp"
#include "Animation/AnimationManager.hpp"
#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include "GameHandle.hpp"
#include "MapManager.hpp"

namespace App
{
	enum		eScope
	{
		LOCAL = 0,
		NETWORK
	};


	class GameClient : public AState
	{

	private:
		GameHandler																	handler_;
		Asset::AGameObject*													player_;
		std::vector<Asset::AGameObject*>						firePlayerVector_;
		std::map<unsigned int, Asset::AGameObject*>	bulletGameObjectMap_;
		std::map<unsigned int, Asset::AGameObject*>	gameObjectMap_;
		std::map<unsigned int, Asset::AGameObject*>	mapObjects_;
		std::map<float, std::string*>								beamLevelMap_;
		std::vector<std::string>										colorShipVector_;
		std::map<Asset::ePowerUpType, void (GameClient::*)()>			powerUpMap_;
		int																					playerId_;
                unsigned int currentMapId_;
		float																				timer_;
		float																				beamValue_;
		bool																				isBeam_;
		bool																				gameOver_;	
		int																					width_;
		int																					height_;
		unsigned int																count_;
		Network::TCPClient													*socketTCP_;
		Thread::Mutex																mutex_;
                Asset::MapManager mapManager_;
		int																	weaponLevel_;
		int																	speedLevel_;

	public:
		GameClient(Network::UDPSocket*);
		~GameClient();
		void	initialize();
		void	resetGame();
		void	draw(sf::RenderWindow*);
		void	onPressedKey(sf::Event);
		void	update(Network::Packet const &);
		void	update(float);
		void	activateCheatCode();
		int		getHeight() const;
		int		getWidth() const;
		int		getPlayerId() const;
		void	setGameOver(bool);
		bool	getGameOver() const;
		int		getWeaponLevel() const;
		Asset::AGameObject*								createGameObject(const std::string &, const std::string &, float, 
																		float, unsigned int, bool, const Asset::AGameObject *, eScope);
		std::map<unsigned int, Asset::AGameObject*>&	getGameObjectMap();
		std::map<unsigned int, Asset::AGameObject*>&	getBulletGameObjectMap();
		std::vector<Asset::AGameObject*>&				getFirePlayerVector();
		void	gameOver();
		void	activatePowerUp(Asset::ePowerUpType);
	private:
		void				initObject(Asset::AGameObject *, const std::string &, float, 
										float, unsigned int, bool, const Asset::AGameObject *);
		void				manageDeath(Asset::AGameObject *, bool);
		float				manageBullet(float);
		const std::string&	getBeamLevel(float) const;
		void				initialiseWeapon2();
		void				initialiseWeapon3();
		void				initialiseWeapon4();
		void				initialiseWeapon5();
		
		void				initialiseModule();

		void				increaseSpeed();


                template<typename T>
                  void  updateMap(float time, std::map<T,
                    Asset::AGameObject*> &map)
                {
                  typename std::map<T, Asset::AGameObject*>::iterator toDel;
                  typename std::map<T, Asset::AGameObject*>::iterator it;
                  bool                                                notExplosion = false;

                  for (it = map.begin(); it != map.end();)
                  {
                    if (it->second->getGameObjectType() == Asset::PLAYER)
                    {
                      Protocol::eEvent key = EventManager::getInstance().getDirection();

                      this->handler_.sendEvent(this->playerId_, key);
                      Animation::AnimationManager::getInstance().update(time, *(it->second), key);
                    }
                    else
                      Animation::AnimationManager::getInstance().update(time, *(it->second));
                    notExplosion = it->second->updateStatus(App::WIDTH, App::HEIGHT);
                    if (it->second->getDeath())
                    {
                      manageDeath(it->second, notExplosion);
                      toDel = it++;
                      delete toDel->second;
                      map.erase(toDel);
                    }
                    else
                      ++it;
                  }
                }

                template<typename T>
                  void drawMap(sf::RenderWindow *window, std::map<T, Asset::AGameObject*> map)
                  {
                    typename std::map<T, Asset::AGameObject*>::iterator it;
                    for (it = map.begin(); it != map.end(); ++it)
                      Animation::AnimationManager::getInstance().draw(*window, *it->second);
                  }
        };
}

#endif
