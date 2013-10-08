#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <queue>
#include "Packet.hpp"
#include "TCPSocket.hpp"

namespace Game
{

  class			Player
  {
  private:
    typedef int		UDPSocket;
    Network::TCPSocket	*tcpSocket_;
    UDPSocket		udpSocket_;
    struct sockaddr_in	sock_;

  private:
    std::string		room_;
    std::string		id_;
    unsigned int		score_;
    std::queue<Network::Packet*> toSendMessages_;
    bool			isReady_;
    unsigned int              color_;

  public:
    Player(struct sockaddr &sock);
    ~Player();

  private:
    Player();

  public:
    std::string const& getId() const;
    void setId(std::string const& id);
    std::string const& getRoom() const;
    void setRoom(std::string const& room);

    unsigned int getScore() const;
    void setScore(unsigned int);
    void addToScore(unsigned int);

    Network::TCPSocket* getTCPSocket();
    void setTCPSocket(Network::TCPSocket *socket);

    struct sockaddr_in* getSockAddr();
    UDPSocket const& getUDPSocket() const;

    Network::Packet* popPacket();
    void pushPacket(Network::Packet* packet);

    void setReady(bool ready);
    bool isReady() const;

    bool isPacketIn() const;

    unsigned int getColor() const;
    void setColor(unsigned int);
    void setUDPPort(unsigned int);

  private:
    Player(Player const&);
    Player& operator=(Player const&);
  };

}

#endif
