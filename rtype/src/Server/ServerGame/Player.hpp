#ifndef			PLAYER_HPP
# define		PLAYER_HPP

# include		"TCPSocket.hpp"
# include		"UDPSocket.hpp"
# include		"Module.hpp"

namespace		ServerGame
{
  class			Player
  {
    unsigned int	level_;
    int			score_;
    Module		module_;
    float		beam_;
    TCPSocket		tcpClient_;
    UDPSocket		udpClient_;

  public:
    void		setLevel(unsigned int level);
    void		setFire(bool fire);
    
  public:
    unsigned int	getLevel() const;
  };
}

#endif			/* PLAYER_HPP */
