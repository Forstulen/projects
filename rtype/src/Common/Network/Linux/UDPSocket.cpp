#include		<stdio.h>
#include		<iostream>
#include		<sys/types.h>
#include		<sys/socket.h>
#include		<arpa/inet.h>
#include		<errno.h>
#include		<cstring>
#include		<sys/ioctl.h>

#include		"UDPSocket.hpp"

Network::UDPSocketLinux::UDPSocketLinux()
  : fd_(socket(AF_INET, SOCK_DGRAM, 0)),
    port_(0)
{
  int		arg = 1;

  ioctl(this->fd_, FIONBIO, &arg);
}

Network::UDPSocketLinux::UDPSocketLinux(unsigned int const port)
  : fd_(socket(AF_INET, SOCK_DGRAM, 0)),
    port_(port)
{
}

Network::UDPSocketLinux::~UDPSocketLinux()
{
  close(this->fd_);
}

void			Network::UDPSocketLinux::setPort(unsigned int const port)
{
  this->port_ = port;
}

unsigned int		Network::UDPSocketLinux::bindSocket() throw (CodeExcept)
{
  struct sockaddr_in	sAddr;

  sAddr.sin_family = AF_INET;
  sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sAddr.sin_port = 0;

  if (bind(this->fd_, (struct sockaddr*)&sAddr, sizeof(sAddr)) == -1)
    throw ErrnoExcept("UDPSocketLinux::bindSocket");

  socklen_t		len = sizeof(sAddr);
  if (getsockname(this->fd_, (struct sockaddr*)&sAddr, &len) != 0)
    std::cout << "error getsokname" << std::endl;
  std::cout << "port UDP : " << ntohs(sAddr.sin_port) << std::endl;
  return ntohs(sAddr.sin_port);
}

bool			Network::UDPSocketLinux::sendPacket(Packet const &p, struct sockaddr const* addr) const
{
  if (sendto(this->fd_, &p.getContent(), p.getSize(), 0, addr, sizeof(*addr)) == -1)
    {
      std::cout << strerror(errno) << std::endl;
      return (false);
    }
  return (true);
}

Network::Packet*	Network::UDPSocketLinux::recvPacket(struct sockaddr *addr) const
{
  Network::Content	content;
  socklen_t		addrlen = Network::maxData;

  if (recvfrom(this->fd_, &content, Network::maxData, MSG_DONTWAIT, addr, &addrlen) == -1)
    return (NULL);
  Packet *packet = new Packet(content);
  return packet;
}

int			Network::UDPSocketLinux::getSocket() const
{
  return this->fd_;
}
