#include	<iostream>

#include "TCPSocket.hpp"
#include "Player.hpp"

namespace Game
{

  Player::Player(struct sockaddr &sock):
    tcpSocket_(0), isReady_(false), score_(0)
  {
    this->sock_.sin_family = AF_INET;
    this->sock_.sin_addr = ((struct sockaddr_in*)&sock)->sin_addr;
  }

  Player::~Player()
  {
  }

  std::string const& Player::getId() const
  {
    return this->id_;
  }

  void Player::setId(std::string const& id)
  {
    this->id_ = id;
  }

  std::string const& Player::getRoom() const
  {
    return this->room_;
  }

  void Player::setRoom(std::string const& room)
  {
    this->room_ = room;
  }

  unsigned int Player::getScore() const
  {
    return this->score_;
  }

  void Player::setScore(unsigned int score)
  {
    this->score_ = score;
  }

  void Player::addToScore(unsigned int score)
  {
    this->score_ += score;
  }

  Network::TCPSocket* Player::getTCPSocket()
  {
    return this->tcpSocket_;
  }

  void Player::setTCPSocket(Network::TCPSocket *socket)
  {
    this->tcpSocket_ = socket;
  }

  struct sockaddr_in* Player::getSockAddr()
  {
    return &this->sock_;
  }

  int const& Player::getUDPSocket() const
  {
    return this->udpSocket_;
  }

  Network::Packet* Player::popPacket()
  {
    Network::Packet *tmpPtr;
    if (!this->toSendMessages_.empty())
      tmpPtr = toSendMessages_.front();
    else
      tmpPtr = 0;
    toSendMessages_.pop();
    return tmpPtr;
  }

  void Player::pushPacket(Network::Packet* packet)
  {
    this->toSendMessages_.push(packet);
  }

  void Player::setReady(bool ready)
  {
    this->isReady_ = ready;
  }

  bool Player::isReady() const
  {
    return this->isReady_;
  }

  bool Player::isPacketIn() const
  {
    return !this->toSendMessages_.empty();
  }
  unsigned int Player::getColor() const
  {
    return this->color_;
  }

  void Player::setColor(unsigned int color)
  {
    this->color_ = color;
  }

  void Player::setUDPPort(unsigned int port)
  {
    this->sock_.sin_port = htons(port);
  }
}
