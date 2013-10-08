#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <list>
#include <string>
#include "Player.hpp"
#include "UDPSocket.hpp"
#include "Timer.hpp"
#include "Table.hpp"
#include "Conversions.hpp"
#include "AGameObject.hpp"

namespace Game
{
  class Game;
  class Level
  {
    typedef std::multimap<float, Asset::AGameObject*> ObjectMap;

    ObjectMap    poolObjects_;
    Level        *nextLevel_;
    unsigned int currentId_;
    Network::UDPSocket& socket_;

  public:
    Level(std::string const&, Network::UDPSocket& socket);
    ~Level();

    void  setNextLevel(Level *);
    Level *getNextLevel() const;
    void  popObjects(std::map<unsigned int, Asset::AGameObject*>&,
		     std::list<Player*>&, sf::Clock&, Game &g);
    void  initLevel(std::list<Player*>& players, std::map<unsigned int, Asset::AGameObject*>& aliveObjects);

    void sendPacketInGame(std::list<Player*>& players, Network::Packet const & packet) const;

  private:
    void fillObjectData(Asset::AGameObject* obj, Protocol::ObjectData &data, float timer) const;

  private:
    bool insertLibraryObject(RTDB::Table::Rows::const_iterator &it);

  public:
    void sendCreation(std::list<Player*>&, Asset::AGameObject*,
		      float timer);
    void sendModification(std::list<Player*>&, Asset::AGameObject*,
			  float timer);
    void sendDestruction(std::list<Player*>& players, Asset::AGameObject* obj,
			 float timer);
  };
}

#endif
