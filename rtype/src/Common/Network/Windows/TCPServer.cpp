#include		"TCPServer.hpp"

Network::TCPServerWindows::TCPServerWindows() : TCPSocket()
{
}

Network::TCPServerWindows::TCPServerWindows(std::string const &host,
					    unsigned int const port)
  : TCPSocket(host, port)
{
}

Network::TCPServerWindows::~TCPServerWindows(){}

Network::TCPSocket *		Network::TCPServerWindows::acceptClient(SOCKADDR &sockaddr)
{
  int							len = sizeof(sockaddr);
  SOCKET					socketClient = WSAAccept(this->fd_, &sockaddr, &len, NULL, NULL);

  if (socketClient == INVALID_SOCKET)
    return NULL;
  return new TCPSocket(socketClient);
}

bool		Network::TCPServerWindows::listenSocket()
{
  return (listen(this->fd_, 1000) == 0);
}
