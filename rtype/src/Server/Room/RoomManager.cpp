#include <string>
#include <algorithm>
#include <iostream>

#include "RoomManager.hpp"
#include "Player.hpp"
#include "Room.hpp"
#include "Protocol.hpp"
#include "Conversions.hpp"

namespace			Room
{
  RoomManager::RoomManager()
  {
    this->initFunctions();
    this->initRooms();
  }
  
  RoomManager::~RoomManager() {}

  void				RoomManager::initFunctions()
  {
    this->functions_[Conversions::encodeToUShort(Protocol::RT_TYPE_ROOM, 
						 Protocol::RT_SUB_JOIN)]
      = &RoomManager::forRoom;
    this->functions_[Conversions::encodeToUShort(Protocol::RT_TYPE_ROOM, 
						 Protocol::RT_SUB_LEAVE)]
      = &RoomManager::forRoom;
    this->functions_[Conversions::encodeToUShort(Protocol::RT_TYPE_ROOM, 
						 Protocol::RT_SUB_READY)]
      = &RoomManager::forPlayerRoom;
    this->functions_[Conversions::encodeToUShort(Protocol::RT_TYPE_ROOM, 
						 Protocol::RT_SUB_ROOMS)]
      = &RoomManager::roomsName;
    this->functions_[Conversions::encodeToUShort(Protocol::RT_TYPE_ROOM, 
						 Protocol::RT_SUB_PLAYERS)]
      = &RoomManager::forRoom;
    this->functions_[Conversions::encodeToUShort(Protocol::RT_TYPE_ROOM,
						 Protocol::RT_SUB_INFO)]
      = &RoomManager::forPlayerRoom;
    this->functions_[Conversions::encodeToUShort(Protocol::RT_TYPE_ROOM,
						 Protocol::RT_SUB_START)]
      = &RoomManager::forPlayerRoom;
  }

  void				RoomManager::initRooms()
  {
    this->createRoom("R-9a", 4243);
    this->createRoom("Bydo", 4244);
    this->createRoom("Round Canopy", 4245);
    this->createRoom("1987", 4246);
    this->createRoom("Dobkeratops", 4247);
    this->createRoom("Gomander", 4248);
    this->createRoom("Warship", 4249);
    this->createRoom("Womb", 4250);
    this->createRoom("BEAM", 4251);
    this->createRoom("???", 4252);
  }

  void				RoomManager::createRoom(std::string const & roomName, unsigned int port)
  {
    Room *			newRoom = new Room(roomName, port);

    this->rooms_[roomName] = newRoom;
  }

  bool				RoomManager::handlePacket(Game::Player *player, Network::Packet *packet)
  {
    unsigned short		opcode;
    tFunctionContainer::iterator itFunct;

    opcode = Conversions::encodeToUShort(packet->getType(), packet->getSubType());
    if ((itFunct = this->functions_.find(opcode)) != this->functions_.end())
      {
	RMMemFn funct = (*itFunct).second;
	return (this->*funct)(player, packet);
      }
    return false;
  }

  bool				RoomManager::forRoom(Game::Player *player, Network::Packet *packet)
  {
    char const *		data(packet->getData<char const *>());
    std::string			roomName(data);	
    tRoomContainer::iterator	itRoom;

    if ((itRoom = rooms_.find(roomName)) != rooms_.end())
      {
	if (packet->getSubType() == Protocol::RT_SUB_JOIN)
	  {
	    this->players_.push_back(player);
	    itRoom->second->handlePacket(player, packet);
	  }
	else if (packet->getSubType() == Protocol::RT_SUB_LEAVE)
	  this->delPlayer(player);
	else
	  itRoom->second->handlePacket(player, packet);
	return true;
      }
    else
      {	
	std::string		error("This room doesn't exists.\n");
	Network::Packet *	toSend = new Network::Packet(error.c_str(), 
							     error.size(),
							     Protocol::RT_TYPE_ROOM,
							     Protocol::RT_TT_ERROR,
							     packet->getSubType());
	player->pushPacket(toSend);
      }
    delete packet;
    return false;
  }

  Game::Player *		RoomManager::findPlayer(Game::Player *player)
  {
    tPlayerContainer::iterator	itPlayer;
    
    itPlayer = std::find(this->players_.begin(), this->players_.end(), player);
    if (itPlayer != this->players_.end())
      return (*itPlayer);
    else return 0;
  }

  bool				RoomManager::addPlayer(Game::Player *player)
  {
    if (!findPlayer(player))
      return false;
    players_.push_back(player);
    return true;
  }

  bool				RoomManager::delPlayer(Game::Player *player)
  {
    tPlayerContainer::iterator	itPlayer;
    
    itPlayer = std::find(this->players_.begin(), this->players_.end(), player);
    if (itPlayer != this->players_.end())
      {
	players_.erase(itPlayer);
        if (this->rooms_.find(player->getRoom()) != this->rooms_.end())
          rooms_[player->getRoom()]->delPlayer(player);
	return true;
      }
    return false;
  }

  bool				RoomManager::roomsName(Game::Player *player, Network::Packet *packet)
  {
    tRoomContainer::iterator	itRoom = this->rooms_.begin();
    std::string			listRoom;
    
    for (; itRoom != this->rooms_.end(); ++itRoom)
      {
	listRoom.append(itRoom->second->getName());
	listRoom.append(1, '\0');
      }
    
    Network::Packet *		 toSend = new Network::Packet(listRoom.c_str(),
							      listRoom.size(),
							      Protocol::RT_TYPE_ROOM,
							      Protocol::RT_TT_REPLY,
							      Protocol::RT_SUB_ROOMS);
    player->pushPacket(toSend);
    return true;
  }

  bool				RoomManager::forPlayerRoom(Game::Player *player, Network::Packet* packet)
  {
    if (player->getRoom().size() != 0
        && this->rooms_.find(player->getRoom()) != this->rooms_.end())
      {
	this->rooms_[player->getRoom()]->handlePacket(player, packet);
	return true;
      }
    return false;
  }
}
