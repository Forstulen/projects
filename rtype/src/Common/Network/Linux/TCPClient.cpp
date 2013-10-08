#include		<unistd.h>
#include		<netdb.h>
#include		<sstream>

#include		"TCPClient.hpp"

Network::TCPClientLinux::TCPClientLinux() : TCPSocket()
{
}

Network::TCPClientLinux::TCPClientLinux(std::string const &host,
					unsigned int const port)
  : TCPSocket(host, port)
{
}

Network::TCPClientLinux::~TCPClientLinux(){}

bool			Network::TCPClientLinux::connectToServer()
{
  struct addrinfo	adr_info;
  struct addrinfo	*addr_res;
  bool			ret;
  int			res;
  std::ostringstream	oss;

  adr_info.ai_flags = 0;
  adr_info.ai_family = AF_INET;
  adr_info.ai_socktype = SOCK_STREAM;
  adr_info.ai_protocol = 0;
  adr_info.ai_addrlen = 0;
  adr_info.ai_addr = NULL;
  adr_info.ai_canonname = NULL;
  adr_info.ai_next = NULL;

  oss << this->port_;
  res = getaddrinfo(this->host_.c_str(), oss.str().c_str(), &adr_info, &addr_res);
  if (res != 0)
    throw (CodeExcept(res, "TCPCLientLinux::connectToServer:getaddrinfo"));
  ret = (connect(this->fd_, addr_res->ai_addr, addr_res->ai_addrlen) == 0);
  freeaddrinfo(addr_res);
  return ret;
}
