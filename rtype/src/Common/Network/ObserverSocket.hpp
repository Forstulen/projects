#ifndef		OBSERVER_SOCKET_HPP
#define		OBSERVER_SOCKET_HPP

#include	<list>
#include	<algorithm>

#include	"IObserver.hpp"
#include	"ISocket.hpp"
#include	"IThread.hpp"

namespace	Network
{

  class				ObserverSocket : public IObserver
  {

    std::list<IListener *>	listeners_;
    Packet *			packet_;
    bool			end_;
    ISocket *			socket_;
    Thread::IThread *		thread_;
    fd_set				readfds_;
    struct timeval timev_;

  public:

    ObserverSocket(ISocket *socket);
    ~ObserverSocket();

    void			registerListener(IListener *);
    void			notifyListener(IListener *);
    void			notifyListeners();

  public:

    void			observeSocket();

	private:
		void			doSelect();
  };

};

#endif
