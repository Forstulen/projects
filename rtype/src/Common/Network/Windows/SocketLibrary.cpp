#include		<iostream>
#include		<winsock2.h>
#include		"SocketLibrary.hpp"

Network::SocketLibrary::SocketLibrary()
{
  WORD		wVersionRequested;
  WSADATA	wsaData;

  wVersionRequested = MAKEWORD(2, 2);
  if (WSAStartup(wVersionRequested, &wsaData) != NO_ERROR)
    std::cerr << "Error initializing Socket client." << std::endl;
}

Network::SocketLibrary::~SocketLibrary()
{
  if (WSACleanup())
    std::cerr << "Error when close lbrary." << std::endl;
}
