#ifndef		ITCPSERVER_HPP
#define		ITCPSERVER_HPP

#include	"ITCPClient.hpp"
#include	"ISocket.hpp"

namespace	Network
{

  class			ITCPServer
  {

  public:

    virtual		~ITCPServer(){}

    virtual ISocket	*acceptClient(struct sockaddr&) = 0;
    virtual bool	listenSocket() = 0;

  };


};

#endif
