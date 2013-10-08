#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include <string>
#include <map>
#include "CoreRTYPE.hpp"
#include "Packet.hpp"
#include "EventManager.hpp"
#include "UDPSocket.hpp"
#include "TCPClient.hpp"
#include "AGameObject.hpp"
#include "LoaderManager.hpp"
#include "Mutex.hpp"
#include "ScopedLock.hpp"
#include "Packet.hpp"
#include "HUDManager.hpp"

namespace App
{
  class GameClient;

  class GameHandler
  {
  private:
    typedef void (GameHandler::*GCMemFn)(Network::Packet const &);
    typedef std::map<unsigned int, GCMemFn>				tFunctionContainer;
    GameClient												&game_;
    Network::UDPSocket										*socketUDP_;
    Protocol::eEvent										lastKey_;
    unsigned int											count_;
    tFunctionContainer										functions_;
    Thread::Mutex											mutex_;
    struct sockaddr_in										sockAddr_;

  public:
    GameHandler(Network::UDPSocket*, GameClient &, Thread::Mutex&);
    ~GameHandler();
    void	initFunctions();
    void	initHandler();

    void	handleEvent(Network::Packet const &data);
    void	handleObject(Network::Packet const &data);
    void	handleBullet(Network::Packet const &data);
    void	handleScore(Network::Packet const &data);
		void	handleGameOver(Network::Packet const &data);

    void	createGameObject(Network::Packet const &data);
    void	modifyGameObject(Network::Packet const &data);
    void	destroyGameObject(Network::Packet const &data);

    void	modifyPlayerObject(Network::Packet const &data);

    void	createBulletObject(Network::Packet const &data);
    void	modifyBulletObject(Network::Packet const &data);
    void	destroyBulletObject(Network::Packet const &data);

    void	update(Network::Packet const& packet);
    void	sendEvent(int, Protocol::eEvent);
    void	sendFire(int, const Asset::AGameObject&, const std::string &);
    void	sendUDPPacket(Network::Packet const&);
  };
}

#endif	//	GAMEHANDLER_HPP
