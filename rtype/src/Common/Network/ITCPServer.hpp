#ifndef		ITCPSERVER_HPP
#define		ITCPSERVER_HPP

#include	"ISocket.hpp"

namespace	Network
{

  class			ITCPServer
  {

  public:

    virtual		~ITCPServer(){}

    virtual ISocket	*acceptClient(struct sockaddr &sock) = 0;
    virtual bool	listenSocket() = 0;

  };


};

#endif
