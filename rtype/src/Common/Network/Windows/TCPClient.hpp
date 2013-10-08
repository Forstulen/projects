#ifndef		TCPCLIENTWINDOWS_HPP
#define		TCPCLIENTWINDOWS_HPP

#include	"ITCPClient.hpp"
#include	"TCPSocket.hpp"

namespace	Network
{

  class		TCPClientWindows : public ITCPClient, public TCPSocket
  {

  public:

    TCPClientWindows();
    TCPClientWindows(std::string const &host, unsigned int const port);
    ~TCPClientWindows();

    bool		connectToServer();

  };

  typedef		TCPClientWindows	TCPClient;

};

#endif
