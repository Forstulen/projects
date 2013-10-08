#ifndef		TCPSOCKETLINUX_HPP
#define		TCPSOCKETLINUX_HPP

#include	"ISocket.hpp"

namespace	Network
{

  class		TCPSocketLinux : public ISocket
  {

  protected:

    int			fd_;
    std::string		host_;
    unsigned int	port_;

  public:

    TCPSocketLinux();
    TCPSocketLinux(int const socket);
    TCPSocketLinux(std::string const &host, unsigned int const port);
    ~TCPSocketLinux();

    void		setPort(unsigned int const port);
    void		setHost(std::string const & host);

    unsigned int	bindSocket() throw (CodeExcept);
    bool		sendPacket(Packet const &, struct sockaddr const*sockAddr) const;
    Packet*		recvPacket(struct sockaddr *sockAddr) const;

    int			getSocket() const;

  };

  typedef		TCPSocketLinux	TCPSocket;

};

#endif
