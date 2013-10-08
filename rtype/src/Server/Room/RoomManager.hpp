#ifndef ROOMMANAGER_HPP
#define ROOMMANAGER_HPP

#include <string>
#include <map>
#include <list>

#include "Player.hpp"
#include "Packet.hpp"
#include "Room.hpp"

namespace					Room
{
  class						RoomManager
  {
  private:
    typedef std::map<std::string const, Room *>			tRoomContainer;
    typedef std::list<Game::Player*>				tPlayerContainer;
    typedef bool (RoomManager::*RMMemFn)(Game::Player*, Network::Packet*);
    typedef std::map<unsigned short, RMMemFn>			tFunctionContainer;
    
  private:
    tRoomContainer				rooms_;
    tPlayerContainer				players_;
    tFunctionContainer				functions_;
    
  public:
    ~RoomManager();
    RoomManager();
    
  private:
    RoomManager(RoomManager const& other){}
    RoomManager&				operator+=(Room const& other){}
    
  private:
    void					initFunctions();
    void					initRooms();
    void					createRoom(std::string const &, unsigned int);
    bool					forRoom(Game::Player *, Network::Packet*);
    bool					roomsName(Game::Player *, Network::Packet*);
    bool					forPlayerRoom(Game::Player *, Network::Packet*);
    
  public:
    Game::Player* 				findPlayer(Game::Player *);
    bool					addPlayer(Game::Player*);
    bool					delPlayer(Game::Player *);
    bool					handlePacket(Game::Player*, Network::Packet*);
  };
}

#endif
