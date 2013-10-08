#ifndef		TCPSERVERLINUX_HPP
#define		TCPSERVERLINUX_HPP

#include	"ITCPServer.hpp"
#include	"TCPSocket.hpp"

namespace	Network
{

  class		TCPServerLinux : public ITCPServer, public TCPSocket
  {

  public:

    TCPServerLinux();
    TCPServerLinux(std::string const &host, unsigned int const port);
    ~TCPServerLinux();

    TCPSocket		*acceptClient(struct sockaddr &sock);
    bool		listenSocket();

  };

  typedef		TCPServerLinux	TCPServer;

};

#endif
