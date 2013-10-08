#include		<sys/types.h>
#include		<sys/socket.h>
#include		<arpa/inet.h>
#include		<iostream>

#include		"TCPSocket.hpp"
#include		"Conversions.hpp"

Network::TCPSocketLinux::TCPSocketLinux()
  : fd_(socket(AF_INET, SOCK_STREAM, 0)),
    host_("localhost"),
    port_(0)
{
}

Network::TCPSocketLinux::TCPSocketLinux(int const fd)
  : fd_(fd),
    host_("localhost"),
    port_(0)
{
}

Network::TCPSocketLinux::TCPSocketLinux(std::string const &host,
					unsigned int const port)
  : fd_(socket(AF_INET, SOCK_STREAM, 0)),
    host_(host),
    port_(port)
{
}

Network::TCPSocketLinux::~TCPSocketLinux()
{
  close(this->fd_);
}

int			Network::TCPSocketLinux::getSocket() const
{
  return this->fd_;
}

void			Network::TCPSocketLinux::setPort(unsigned int const port)
{
  this->port_ = port;
}

void			Network::TCPSocketLinux::setHost(std::string const & host)
{
  this->host_ = host;
}

unsigned int		Network::TCPSocketLinux::bindSocket() throw (CodeExcept)
{
  struct sockaddr_in	sock_adr;
  int			nb = 1;

  if (setsockopt(this->fd_, SOL_SOCKET, SO_REUSEADDR, &nb, sizeof(nb)) == -1)
    throw ErrnoExcept("TCPSocketLinux::bindSocket");
  sock_adr.sin_family = AF_INET;
  sock_adr.sin_port = htons ((uint16_t const) this->port_);
  sock_adr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(this->fd_, (struct sockaddr *)(&sock_adr), sizeof(sock_adr)) == -1)
    throw ErrnoExcept("TCPSocketLinux::bindSocket");
  return (this->port_);
}

bool			Network::TCPSocketLinux::sendPacket(Packet const &p, struct sockaddr const*sockAddr) const
{
  int			i;

  if ((i = send(this->fd_, &p.getContent(), p.getSize(), 0)) <= 0)
    return (false);
  return (true);
}

Network::Packet*	Network::TCPSocketLinux::recvPacket(struct sockaddr *sockAddr) const
{
  Network::Content	content;
  int			i = 0;
  Packet		*packet = NULL;

  if ((i += recv(this->fd_, &(content.head), sizeof(Network::Header), 0)) <= 0)
    return (NULL);
  if ((i += content.head.size && recv(this->fd_, &content.data, content.head.size, 0)) <= 0)
    return (NULL);
  packet = new Packet(content);
  return packet;
}
