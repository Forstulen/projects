#ifndef		ISOCKET_HPP
#define		ISOCKET_HPP

#ifdef		WIN32
#include	<Winsock2.h>
#endif

#ifdef		__i386
#include	<sys/socket.h>
#include	<sys/types.h>
#include	<arpa/inet.h>
#endif

#include	"ErrnoExcept.hpp"
#include	"CodeExcept.hpp"
#include	"Except.hpp"
#include	"Packet.hpp"

namespace	Network
{

  class			ISocket
  {

  public:

    virtual		~ISocket(){}

    virtual unsigned int		bindSocket() = 0;
    virtual bool		sendPacket(Packet const &, struct sockaddr const*) const = 0;
    virtual Packet	*recvPacket(struct sockaddr*) const = 0;
    virtual int			getSocket() const = 0;

  };

};

#endif
