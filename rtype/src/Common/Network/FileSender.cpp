#include			"FileSender.hpp"

Network::FileSender::FileSender(TCPSocket const & socket) :
  socket_(socket)
{
}

Network::FileSender::~FileSender()
{
}

bool      			Network::FileSender::operator<<(std::string const & filename)
{
  this->queue_.push(filename);
  std::cout << "FileSender: Adding file " << filename << std::endl;
	return true;
}

bool				Network::FileSender::operator--()
{
  std::string			filename;
  std::ifstream			is;
  char				buf[Protocol::maxPacketSize];
  
  if (this->queue_.pop(filename))
    {
      is.open(filename.c_str());
      if (is.is_open())
	while (!is.eof())
	  {
	    is.read(buf, Protocol::maxPacketSize);
	    Packet		packet(buf, is.gcount(),
				       Protocol::RT_TYPE_ROOM,
				       Protocol::RT_TT_MODIFICATION,
				       Protocol::RT_SUB_FILE);
	  }
      Packet			packet("", 0,
				       Protocol::RT_TYPE_ROOM,
				       Protocol::RT_TT_MODIFICATION,
				       Protocol::RT_SUB_FILE);
      this->socket_.sendPacket(packet, 0);
      return (true);
    }
  std::cout << "FileSender: Nothing else to send" << std::endl;
  return (false);
}

bool				Network::FileSender::requestSendFile()
{
  std::string			filename;

  if (this->queue_.top(filename))
    {
      Packet	packet(filename.c_str(), filename.size(),
		       Protocol::RT_TYPE_ROOM,
		       Protocol::RT_TT_CREATION,
		       Protocol::RT_SUB_FILE);
      std::cout << "FileSender: Sending Request for " << filename << std::endl;
      this->socket_.sendPacket(packet, 0);
      return (true);
    }
  std::cout << "FileSender: No more file" << std::endl;
  return (false);
}
