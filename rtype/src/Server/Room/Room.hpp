#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <list>
#include <map>

#include "Player.hpp"
#include "Packet.hpp"
#include "Game.hpp"

namespace					Room
{  
  const unsigned int				MAXPLAYER = 4;

  class						Room
  { 
  private:
    typedef std::list<Game::Player *>		tPlayerContainer;
    typedef bool (Room::*RMemFn)(Game::Player*, Network::Packet*);
    typedef std::map<unsigned short, RMemFn>	tFunctionContainer;

  private:
    tPlayerContainer				players_;
    tFunctionContainer				functions_;
    std::string					roomName_;
    Game::Game                                  game_;
    unsigned int				readyToPlayer_;
    bool					isInGame_;
    
  public:
    ~Room();
    Room(std::string const &, unsigned int);

  private:
    Room();
    Room(Room const& other);
    Room&					operator+=(Room const& other);

  public:
    Room::tPlayerContainer const&		getPlayerContainer() const;
    std::string const &				getName() const;
    unsigned int				nbPlayers() const;
    bool					delPlayer(Game::Player *);
    bool					handlePacket(Game::Player *, Network::Packet *);
    bool					readyPlayer(Game::Player *, Network::Packet *);
    bool					startGame(Game::Player *, Network::Packet *);

  private:
    void					initFunctions();

  private:
    bool					leavePlayer(Game::Player *, Network::Packet *);
    bool					joinPlayer(Game::Player *, Network::Packet *);
    bool					listPlayers(Game::Player *, Network::Packet *);
    bool					isRoomReady();
    bool					infoPlayer();
    bool					setUDPPlayer(Game::Player *, Network::Packet *);
  };
}

#endif
