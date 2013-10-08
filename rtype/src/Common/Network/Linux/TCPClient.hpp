#ifndef		TCPCLIENTLINUX_HPP
#define		TCPCLIENTLINUX_HPP

#include	"ITCPClient.hpp"
#include	"TCPSocket.hpp"

namespace	Network
{

  class		TCPClientLinux : public ITCPClient, public TCPSocket
  {

  public:

    TCPClientLinux();
    TCPClientLinux(std::string const &host, unsigned int const port);
    ~TCPClientLinux();

    bool		connectToServer();

  };

  typedef		TCPClientLinux	TCPClient;

};

#endif
