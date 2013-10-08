#ifndef		UDPSOCKETLINUX_HPP
#define		UDPSOCKETLINUX_HPP

#include	"ISocket.hpp"

namespace	Network
{

  class		UDPSocketLinux : public ISocket
  {

    int			fd_;
    unsigned int	port_;

  public:

    UDPSocketLinux();
    UDPSocketLinux(unsigned int const port);
    ~UDPSocketLinux();

    /// invoque l'appel systeme \c bind (cf. bind(2)) pour lier la socket
    /// au port sur toutes les interfaces.
    ///
    /// Cette methode remplit une addresse de socket struct sockaddr_in
    /// (cf. ip(7)), puis utilise l'appel a  bind.

    void		setPort(unsigned int const port);

    unsigned int	bindSocket() throw (CodeExcept);
    bool		sendPacket(Packet const &, struct sockaddr const*) const;
    Packet*		recvPacket(struct sockaddr *sockAddr) const;
    int			getSocket() const;
  };

  typedef		UDPSocketLinux	UDPSocket;

};

#endif
