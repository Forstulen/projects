#include    <iostream>
#include    <vector>
#ifdef _i386
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#include    "Protocol.hpp"
#include    "Core.hpp"
#include    "Conversions.hpp"
#include    "ErrnoExcept.hpp"

Core::Core()
{
  this->socket_.setHost("0");
}

Core::~Core()
{
}

/********************************************************************************/

void			Core::initFdSetRead()
{
  std::vector<Game::Player *>::const_iterator it2 = this->waiters_.begin();
  Network::TCPSocket const *     sock = NULL;

  FD_ZERO(&this->readSet_);
  FD_SET(this->socket_.getSocket(), &(this->readSet_));
  for (; it2 != this->waiters_.end(); ++it2)
  {
    sock = (*it2)->getTCPSocket();
    if (sock)
      FD_SET(sock->getSocket(), &(this->readSet_));
  }
  std::vector<Game::Player *>::const_iterator it1 = this->players_.begin();
  for (; it1 != this->players_.end(); ++it1)
  {
    sock = (*it1)->getTCPSocket();
    if (sock)
      FD_SET(sock->getSocket(), &(this->readSet_));
  }
}

void			Core::initFdSetWrite()
{
  std::vector<Game::Player *>::const_iterator it1 = this->players_.begin();
  std::vector<Game::Player *>::const_iterator it2 = this->waiters_.begin();
  Network::TCPSocket const *     sock = NULL;

  FD_ZERO(&this->writeSet_);
  for (; it2 != this->waiters_.end(); ++it2)
  {
    sock = (*it2)->getTCPSocket();
    if (sock && (*it2)->isPacketIn())
      FD_SET(sock->getSocket(), &(this->writeSet_));
  }
  for (; it1 != this->players_.end(); ++it1)
  {
    sock = (*it1)->getTCPSocket();
    if (sock && (*it1)->isPacketIn())
      FD_SET(sock->getSocket(), &(this->writeSet_));
  }
}

void			Core::reinitTimer(int const sec, int const usec)
{
  this->timeout_.tv_sec = sec;
  this->timeout_.tv_usec = usec;  
}

/********************************************************************************/

void			Core::accept()
{
  Game::Player    *newPlayer = NULL;
  Network::TCPSocket   *socket;
  struct sockaddr_in	soc;

  if (FD_ISSET(this->socket_.getSocket(), &(this->readSet_)))
  {
    if ((socket = this->socket_.acceptClient((struct sockaddr&)soc)) == NULL)
      std::cerr << "Server: Cannot accept more connection" << std::endl;
      // throw Network::ErrnoExcept("Error: Core::accept");
    else
    {
      std::cout << "[Server] Client connected" << std::endl;
      newPlayer = new Game::Player((struct sockaddr&)soc);
      newPlayer->setTCPSocket(socket);
      this->waiters_.push_back(newPlayer);
      this->rm_.addPlayer(newPlayer);
    }
  }
}

/********************************************************************************/

void				Core::removeUnexpQuit(Network::TCPSocket *sock, Game::Player *player)
{
  this->rm_.delPlayer(player);
  delete sock;
}

void				Core::listenClientsInRooms()
{
  std::vector<Game::Player *>::iterator it = this->players_.begin();
  Network::TCPSocket		  *sock = NULL;
  Network::Packet		  *packet = NULL;

  for (; it != this->players_.end();)
  {
    sock = (*it)->getTCPSocket();
    if (sock && FD_ISSET(sock->getSocket(), &(this->readSet_)))
      {
	if ((packet = sock->recvPacket(0)))
	  {
	    this->rm_.handlePacket(*it, packet);
	    ++it;
	  }
	else
	  {
	    this->removeUnexpQuit(sock, *it);
	    it = this->players_.erase(it);
	  }
      }
    else
      ++it;
  }
}

bool				Core::isExistingLogin(Network::Packet &packet, std::string const &name) const
{
  std::vector<Game::Player *>::const_iterator it = this->players_.begin();

  for (; it != this->players_.end(); ++it)
    {
      if (name == (*it)->getId())
	{
	  packet.setTransactionType(Protocol::RT_TT_ERROR);
	  return (false);
	}
    }
  for (it = this->waiters_.begin(); it != this->waiters_.end(); ++it)
    {
      if (name == (*it)->getId())
	{
	  packet.setTransactionType(Protocol::RT_TT_ERROR);
	  return (false);
	}
    }
  return (true);
}

void				Core::manageWaitersRequest(Network::TCPSocket *sock,
							   Game::Player *player)
{
  Network::Packet		*packet = NULL;
  std::string			name;

  if (!(packet = sock->recvPacket(0)))
    this->removeUnexpQuit(sock, player);
  else if (!this->am_.scanConnectionPacket(*packet, name) || !this->isExistingLogin(*packet, name))
    {
      std::cout << "[Server] A client has failed to connect to the server" << std::endl;
      sock->sendPacket(*packet, 0);
      delete packet;
      delete sock;
      delete (player);
    }
  else
    {
      (player)->setId(name);
      this->players_.push_back(player);
      (player)->pushPacket(packet);
    }
}

void				Core::listenClient()
{
  std::vector<Game::Player *>::iterator it = this->waiters_.begin();
  Network::TCPSocket*		  sock = NULL;

  this->listenClientsInRooms();
  for (; it != this->waiters_.end();)
  {
    sock = (*it)->getTCPSocket();
    if (sock && FD_ISSET(sock->getSocket(), &(this->readSet_)))
    {
      this->manageWaitersRequest(sock, *it);
      it = this->waiters_.erase(it);
    }
    else
      ++it;
  }
}

void			Core::writeClient()
{
  std::vector<Game::Player *>::iterator it = this->players_.begin();
  Network::TCPSocket*     sock = NULL;
  Network::Packet    *packet = NULL;

  for (; it != this->players_.end();)
  {
    sock = (*it)->getTCPSocket();
    if (sock && FD_ISSET(sock->getSocket(), &(this->writeSet_))
        && (packet = (*it)->popPacket()))
      {
	if (!sock->sendPacket(*packet, 0))
	  {
	    this->removeUnexpQuit(sock, *it);
	    it = this->players_.erase(it);
	  }
	else
	  ++it;
	delete packet;
      }
    else
      ++it;
  }
}

/********************************************************************************/

void			Core::doSelect()
{
  if ((this->nbChangeFd_ = select(FD_SETSIZE, &(this->readSet_),
          &(this->writeSet_), 0, 0)) == -1)
    throw Network::ErrnoExcept("Error: Core::select");
}

void			Core::run()
{
  while (true)
  {
    this->initFdSetWrite();
    this->initFdSetRead();
    this->doSelect();
    this->accept();
    this->listenClient();
    this->writeClient();
  }
}

bool			Core::set(std::string const& port)
{
  this->socket_.setPort(Conversions::convertString<int>(port));
  this->socket_.bindSocket();
  return (this->socket_.listenSocket());
}
