#include		<sys/types.h>
#include		<sys/socket.h>
#include		<netdb.h>

#include		"TCPServer.hpp"

Network::TCPServerLinux::TCPServerLinux() : TCPSocket()
{
}

Network::TCPServerLinux::TCPServerLinux(std::string const &host,
					unsigned int const port)
  : TCPSocket(host, port)
{
}

Network::TCPServerLinux::~TCPServerLinux(){}

Network::TCPSocket *Network::TCPServerLinux::acceptClient(struct sockaddr &addr)
{
  socklen_t		len = sizeof(addr);
  int			fd;

  if ((fd = accept(this->fd_, &addr, &len)) == -1)
    return NULL;
  return new TCPSocket(fd);
}

bool		Network::TCPServerLinux::listenSocket()
{
  return (listen(this->fd_, 1000) != -1);
}
