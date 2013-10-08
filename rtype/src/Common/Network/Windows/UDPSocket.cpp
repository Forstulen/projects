#include		<winsock2.h>

#include		"SocketLibrary.hpp"
#include		"Singleton.hpp"
#include		"UDPSocket.hpp"

Network::UDPSocketWindows::UDPSocketWindows()
   : port_(0)
{
	int iResult;
	u_long iMode = 1;
  Tools::Singleton<Network::SocketLibrary>::getInstance();
  if ((this->fd_ = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0)) == INVALID_SOCKET)
    throw CodeExcept(this->fd_, "UDPSocketWindows::Constructor");
	iResult = ioctlsocket(this->fd_, FIONBIO, &iMode);
if (iResult != NO_ERROR)
}

Network::UDPSocketWindows::UDPSocketWindows(unsigned int const port)
	:	port_(port)
{
	int iResult;
	u_long iMode = 1;
  Tools::Singleton<Network::SocketLibrary>::getInstance();
  if ((this->fd_ = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL, 0, 0)) == INVALID_SOCKET)
    throw CodeExcept(this->fd_, "UDPSocketWindows::Constructor");
	iResult = ioctlsocket(this->fd_, FIONBIO, &iMode);
if (iResult != NO_ERROR)
}

Network::UDPSocketWindows::~UDPSocketWindows()
{
}

void			Network::UDPSocketWindows::setPort(unsigned int const port)
{
  this->port_ = port;
}

unsigned int			Network::UDPSocketWindows::bindSocket()
{
  sockaddr_in		sAddr;

  sAddr.sin_family = AF_INET;
  sAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sAddr.sin_port = 0;

  if (bind(this->fd_, reinterpret_cast<SOCKADDR*>(&sAddr), sizeof(sAddr)) != 0)
  {
	  std::cerr << "error bind: " << WSAGetLastError() << std::endl;
	  throw CodeExcept(this->fd_, "TCPSocketWindows::bindSocket");
  }
     
	
	int			len = sizeof(sAddr);
	if (getsockname(this->fd_, (struct sockaddr*)&sAddr, &len) != 0)
		std::cerr << "error getsokname: " << WSAGetLastError() << std::endl;
	return ntohs(sAddr.sin_port);
}

bool			Network::UDPSocketWindows::sendPacket(Packet const &p, struct sockaddr const *sockAddr) const
{
  DWORD			flags = 0;
  DWORD			bytesSent = 0;
  WSABUF		buf;

  buf.len = p.getSize();
  buf.buf = const_cast<char*>(reinterpret_cast<char const *>(&p.getContent()));

	if (WSASendTo(this->fd_,&buf, 1, &bytesSent, 0, sockAddr, sizeof(*sockAddr), 0, 0) == -1)
    return (false);
  return (true);
}

Network::Packet*	Network::UDPSocketWindows::recvPacket(struct sockaddr *sockAddr) const
{
  Network::Content	content;
  int					addrlen;
  WSABUF			buf;
  DWORD				bytes;
  DWORD				flags = 0;

  buf.buf = reinterpret_cast<char *>(&content);
	memset((void*)&content, 0, 256);
  buf.len = 256;
  addrlen = sizeof(*((struct sockaddr_in*)sockAddr));
  if (WSARecvFrom(this->fd_, &buf, 1, &bytes, &flags,	sockAddr, &addrlen, NULL, NULL) == SOCKET_ERROR || bytes <= 0)
    return (NULL);
	Packet *packet = new Packet(content);
  return packet;
}

int			Network::UDPSocketWindows::getSocket() const
{
  return this->fd_;
}


