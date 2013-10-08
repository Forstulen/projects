#ifndef				FILERECEIVER_HPP
# define			FILERECEIVER_HPP

# include			<string>
# include			<fstream>
# include			<iostream>
# include			"Packet.hpp"

/*
**	No need include. Use : g++ -include file
*/

// # include			"Socket.hpp"

/*
**	The template will be longer than now cuz of the policies.
*/

namespace			Network			
{
  class				FileReceiver
  {
    std::ofstream		file_;

  public:
    FileReceiver();
    ~FileReceiver();

  public:
    bool			operator+=(Packet const & packet);
    bool			operator<<(std::string const & filename);
  };
}

#endif				/* ! FILERECEIVER_HPP */
