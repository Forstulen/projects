#include	"TCPSocket.hpp"
#include	"Singleton.hpp"
#include	"SocketLibrary.hpp"
#include	"Conversions.hpp"

Network::TCPSocketWindows::TCPSocketWindows()
  : host_(""),
    port_(0)
{
  Tools::Singleton<Network::SocketLibrary>::getInstance();
  if ((this->fd_ = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0)) == INVALID_SOCKET)
    throw CodeExcept(this->fd_, "TCPSocketWindows::Constructor");
}

Network::TCPSocketWindows::TCPSocketWindows(SOCKET fd)
  : fd_(fd),
    host_(""),
    port_(0)
{
}

Network::TCPSocketWindows::TCPSocketWindows(std::string const &host,
					    unsigned int const port)
  : host_(host),
    port_(port)
{
  Tools::Singleton<Network::SocketLibrary>::getInstance();
  if ((this->fd_ = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0)) == INVALID_SOCKET)
    throw CodeExcept(this->fd_, "TCPSocketWindows::Constructor");
}

Network::TCPSocketWindows::~TCPSocketWindows()
{
  if (closesocket(this->fd_))
		std::cerr << "Error closing socket" << std::endl;
}

void			Network::TCPSocketWindows::setPort(unsigned int const port)
{
  this->port_ = port;
}

void			Network::TCPSocketWindows::setHost(std::string const & host)
{
  this->host_ = host;
}

unsigned int			Network::TCPSocketWindows::bindSocket()
{
  sockaddr_in		sAddrServer;

  sAddrServer.sin_family = AF_INET;
  sAddrServer.sin_addr.s_addr = INADDR_ANY;
  sAddrServer.sin_port = htons(this->port_);

  if (bind(this->fd_, reinterpret_cast<SOCKADDR*>(&sAddrServer), sizeof(sAddrServer)) != 0)
    throw CodeExcept(this->fd_, "TCPSocketWindows::bindSocket");
	return this->port_;
}

bool			Network::TCPSocketWindows::sendPacket(Packet const &p, struct sockaddr const* sockAddr) const
{
  DWORD			flags = 0;
  DWORD			bytesSent = 0;
  WSABUF		buf;

  buf.len = p.getSize();
  buf.buf = const_cast<char*>(reinterpret_cast<char const *>(&p.getContent()));

  if (WSASend(this->fd_, &buf, 1, &bytesSent, 0, NULL, NULL) != 0 || bytesSent != p.getSize())
    return (false);
    // throw CodeExcept(this->fd_, "TCPSocketWindows::bindSocket");
  return (true);
}

int			Network::TCPSocketWindows::getSocket() const
{
  return this->fd_;
}

Network::Packet*	Network::TCPSocketWindows::recvPacket(struct sockaddr* sockAddr) const
{
  Network::Content	content;
  WSABUF		buf;
  DWORD			bytes;
  DWORD			flags;

  flags = 0;
  buf.buf = reinterpret_cast<char*>(&content.head);
	buf.len = sizeof(Network::Header);

  if (WSARecv(this->fd_, &buf, 1, &bytes, &flags, NULL, NULL) == SOCKET_ERROR || bytes <= 0)
    return (NULL);
  buf.buf = reinterpret_cast<char *>(&content.data);
	memset(static_cast<void*>(&content.data), 0, 254);
  buf.len = content.head.size;

  if (buf.len && WSARecv(this->fd_, &buf, 1, &bytes, &flags, NULL, NULL) == SOCKET_ERROR || bytes <= 0)
    return (NULL);
  Packet *packet = new Packet(content);
  return packet;
}
