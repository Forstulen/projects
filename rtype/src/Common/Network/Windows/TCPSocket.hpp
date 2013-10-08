#ifndef		TCPSOCKETWINDOWS_HPP
#define		TCPSOCKETWINDOWS_HPP

#include	<WinSock2.h>
#include "ISocket.hpp"

namespace	Network
{

  class		TCPSocketWindows : public ISocket
  {

  protected:

    SOCKET				fd_;
    std::string		host_;
    unsigned int	port_;
		SOCKADDR			sockAddr_;
  public:
    TCPSocketWindows();
    TCPSocketWindows(SOCKET fd);
    TCPSocketWindows(std::string const &host, unsigned int const port);
    ~TCPSocketWindows();

    /// invoque l'appel systeme \c bind (cf. bind(2)) pour lier la socket
    /// au port sur toutes les interfaces.
    ///
    /// Cette methode remplit une addresse de socket struct sockaddr_in
    /// (cf. ip(7)), puis utilise l'appel a  bind.

    void		setPort(unsigned int const port);
    void		setHost(std::string const & host);

    unsigned int		bindSocket();
    bool		sendPacket(Packet const &, struct sockaddr const*) const;
    Packet*		recvPacket(struct sockaddr*) const;

    int			getSocket() const;
  };

  typedef		TCPSocketWindows	TCPSocket;

};

#endif
