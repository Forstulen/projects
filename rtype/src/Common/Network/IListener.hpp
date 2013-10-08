#ifndef		ILISTENER_HPP
#define		ILISTENER_HPP

#include	"Packet.hpp"

namespace	Network
{
  class			IListener
  {
  public:
		virtual		~IListener() {}
    virtual void	update(Packet const &) = 0;
  };
}

#endif
