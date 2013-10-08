#include	<iostream>
#include	"ObserverSocket.hpp"
#include	"Thread.hpp"
#include	"UDPSocket.hpp"
#include	"TCPSocket.hpp"

static bool	observeSocket(Network::ObserverSocket *observer)
{
  observer->observeSocket();
  return true;
}

Network::ObserverSocket::ObserverSocket(Network::ISocket *socket)
  : packet_(NULL), end_(false), socket_(socket),
    thread_(new Thread::Thread(&::observeSocket, this))
{
}

Network::ObserverSocket::~ObserverSocket()
{
  this->end_ = true;
  delete this->thread_;
}

void		Network::ObserverSocket::registerListener(IListener *listener)
{
  this->listeners_.push_back(listener);
}

void		Network::ObserverSocket::notifyListener(IListener *listener)
{
  listener->update(*(this->packet_));
}

void		Network::ObserverSocket::notifyListeners()
{
  if (this->packet_)
    std::for_each(this->listeners_.begin(), this->listeners_.end(),
		  std::bind1st(std::mem_fun(&Network::ObserverSocket::notifyListener),
			       this));
}

void						Network::ObserverSocket::doSelect()
{
  this->timev_.tv_sec = 0;
  this->timev_.tv_usec = 10;
  FD_ZERO(&this->readfds_);
  FD_SET(this->socket_->getSocket(), &this->readfds_);
  select(FD_SETSIZE, &this->readfds_, 0, 0, &this->timev_);
}

void            Network::ObserverSocket::observeSocket()
{
	struct sockaddr sock;
	while (!this->end_)
	{
		this->doSelect();
		if (this->end_)
			return;
		if (!this->end_ && FD_ISSET(this->socket_->getSocket(), &this->readfds_))
			if (!(this->packet_ = this->socket_->recvPacket(&sock)))
			{
				std::cout << "Disconnected from server" << std::endl;
				this->end_ = true;
				this->packet_ = new Network::Packet("", 0, Protocol::RT_TYPE_CONNECTION, Protocol::RT_TT_REQUEST, Protocol::RT_SUB_DISC);
			}
		this->notifyListeners();
		delete this->packet_;
		this->packet_ = NULL;
	}
}
