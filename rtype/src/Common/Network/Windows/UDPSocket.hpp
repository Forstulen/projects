#ifndef		UDPSOCKETWINDOWS_HPP
#define		UDPSOCKETWINDOWS_HPP

#include	"ObserverSocket.hpp"
#include	"ISocket.hpp"

namespace	Network
{

  class		UDPSocketWindows : public ISocket
  {

    SOCKET				fd_;
    unsigned int	port_;

  public:

    UDPSocketWindows();
    UDPSocketWindows(unsigned int const port);
    ~UDPSocketWindows();

    void		setPort(unsigned int const port);

    unsigned int	bindSocket();
    bool			sendPacket(Packet const &p, struct sockaddr const*) const;
    Packet*		recvPacket(struct sockaddr*) const;

    int			getSocket() const;
  };

  typedef		UDPSocketWindows	UDPSocket;

};

#endif
