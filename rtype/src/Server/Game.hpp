#ifndef				GAME_HPP
#define				GAME_HPP

#include			<list>
#include			<map>
#include			<utility>
#include			<SFML/System.hpp>

#include			"Level.hpp"
#include			"Thread.hpp"
#include			"AGameObject.hpp"
#include			"UDPSocket.hpp"
#include			"GameHandler.hpp"
#include			"QuadTree.hpp"
#include			"MapManager.hpp"

namespace			Game
{
  class Player;

  class				Game
  {
  public:
    typedef std::multimap<float, Asset::AGameObject*> tObjectMap;
    typedef std::map<unsigned int, Asset::AGameObject*> tAliveObjects;
    typedef std::list<Player*> tPlayerList;

  private:
    tObjectMap		poolObject_;
    tAliveObjects		aliveObjects_;
    QuadTree<Asset::AGameObject>			quadTree_;
    tPlayerList               *playerList_;
    sf::Clock		loopTimer_;
    sf::Clock		gameTimer_;
    Thread::Thread		*thread_;
    Network::UDPSocket	udpsock_;
    Level                     *level_;
    GameHandler               gameHandler_;
    unsigned int		port_;
    bool			inGame_;
    unsigned int		currentId_;
    unsigned int                nextTarget_;
    unsigned int		nbPlayer_;
    Asset::MapManager           mapManager_;
		std::map<Asset::ePowerUpType, Asset::AGameObject* (Game::*)()>			powerUpMap_;

  public:
    Game(unsigned int port);
    ~Game();

  private:
    Game();

  public:
    void				start(std::list<Player*> *list);
    void				run();

  public:
    bool				getInGame() const;
    unsigned int			getPort() const;
    void				popPoolObject();
    void				killingSpree();
    void				eraseDiscPlayers();
    void				recordScore(std::pair<int, int> const & pair);

  private:
    bool                                incNextTarget();
    bool				objectsBehavior(tAliveObjects::iterator & it, float time);
    void				killGameObject(int id);
    void				sendNewScore(tAliveObjects::iterator const & itPl, int const score);
    void				updateAliveObjects(float time);
    void				makeAlive(tAliveObjects::iterator &);
    bool				tookBonuses(tAliveObjects::iterator &it1,
						    tAliveObjects::iterator &it2);
		Asset::AGameObject *				createWeapon2();
		Asset::AGameObject *				createWeapon3();
		Asset::AGameObject *				createWeapon4();
		Asset::AGameObject *				createWeapon5();
		Asset::AGameObject *				increaseSpeed();
		Asset::AGameObject *				createModule();
  
  public:
    void				sendGameOver();

  public:
    tAliveObjects&			getAliveObjects();
    tPlayerList*			getPlayers();
    Network::UDPSocket			&getUDPSocket();
    unsigned int			getCurrentId() const;
    float				getElapsedTime() const;
    Asset::AGameObject			*createBullet(std::string const& name, unsigned char beam, float
						      posX, float posY, int parentId, bool direction, Asset::eGroupObject);
    void				incId();

  private:
    Game(Game const&);
    Game& operator=(Game const&);

    void				initMap();
    void				popPowerUp(Asset::AGameObject*);
  };

  const float				height = 480;
  const float				width = 800;
};

#endif
