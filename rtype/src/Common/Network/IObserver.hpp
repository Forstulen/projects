#ifndef		IOBSERVER_HPP
#define		IOBSERVER_HPP

#include	"IListener.hpp"

namespace	Network
{

  class			IObserver
  {

  public:

    virtual		~IObserver(){}

    virtual void	registerListener(IListener *) = 0;
    virtual void	notifyListener(IListener *) = 0;
    virtual void	notifyListeners() = 0;

  };

};

#endif
