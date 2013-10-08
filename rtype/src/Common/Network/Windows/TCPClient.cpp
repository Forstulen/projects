#include		"TCPClient.hpp"
#include <iostream>

Network::TCPClientWindows::TCPClientWindows() : TCPSocket()
{
}

Network::TCPClientWindows::TCPClientWindows(std::string const &host,
					    unsigned int const port)
  : TCPSocket(host, port)
{
}

Network::TCPClientWindows::~TCPClientWindows(){}

bool			Network::TCPClientWindows::connectToServer()
{
  struct sockaddr_in	sAddr;
  struct sockaddr*	addr;

  addr = reinterpret_cast<SOCKADDR*>(&sAddr);
  sAddr.sin_family = AF_INET;
  sAddr.sin_port = htons(this->port_);
  sAddr.sin_addr.s_addr = inet_addr(this->host_.c_str());

  if (WSAConnect(this->fd_, addr, sizeof(sAddr), NULL, NULL, NULL, NULL) != 0)
	{
		std::cerr << "TCPSocket: Error connecting : " << WSAGetLastError() << std::endl;
    return false;
	}
  return true;
}

