#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include "Protocol.hpp"

namespace Game
{
  class Game;

  class GameHandler
  {
    typedef void (GameHandler::*tHandler)(Network::Packet const&, Player*);
    typedef std::map<unsigned int, tHandler> tHandlers;

    Game      &game_;
    tHandlers handlers_;
    float     timestamp_;

    public:
      GameHandler(Game& g);
      ~GameHandler();

      void receivePackets(float timer);
      void sendDisc(Player *player);
    private:
      GameHandler();

      void allPacket(Network::Packet const&, Player*);
      void bulletHandler(Network::Packet const&, Player*);
      void eventHandler(Network::Packet const&, Player*);
  };
}

#endif
