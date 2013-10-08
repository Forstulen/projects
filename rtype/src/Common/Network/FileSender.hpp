#ifndef				FILESENDER_HPP
# define			FILESENDER_HPP

# include			<string>
# include			<fstream>
# include			<iostream>

# include			"Packet.hpp"
# include			"SafeQueue.hpp"
# include			"TCPSocket.hpp"

namespace			Network			
{
  class				FileSender
  {
    TCPSocket		 const &socket_;
    Thread::SafeQueue<std::string> queue_;

  public:
    FileSender(TCPSocket const & socket);
    ~FileSender();

  public:
    bool      			operator<<(std::string const & filename);
    bool			operator--();

  public:
    bool			requestSendFile();
  };
}

#endif				/* ! FILESENDER_HPP */
