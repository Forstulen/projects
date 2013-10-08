#ifndef		TCPSERVERWINDOWS_HPP
#define		TCPSERVERWINDOWS_HPP

#include <WinSock2.h>
#include	"ITCPServer.hpp"
#include	"TCPSocket.hpp"

namespace	Network
{

  class		TCPServerWindows : public ITCPServer, public TCPSocket
  {
  public:

    TCPServerWindows();
    TCPServerWindows(std::string const &host, unsigned int const port);
    ~TCPServerWindows();

		TCPSocket		*acceptClient(struct sockaddr &);
    bool				listenSocket();

  };

  typedef		TCPServerWindows	TCPServer;

};

#endif
