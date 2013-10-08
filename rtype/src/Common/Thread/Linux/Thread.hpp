#ifndef		THREADLINUX_HPP
#define		THREADLINUX_HPP

#include	<pthread.h>
#include	"IThread.hpp"

/**
 * \file	ThreadLinux.hpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \brief	Thread for Linux
 * \namespace	Thread
 */

namespace	Thread
{

  /**
   * \class		ThreadLinux
   */

  class			ThreadLinux : public IThread
  {

    pthread_t		thread_;

  public:

  template		<typename T, typename U>
  ThreadLinux(T (*routine)(U), U arg)
    {
      pthread_create(&(this->thread_), NULL,
		     reinterpret_cast<IThread::start_routine>(routine), arg);
    }

    ~ThreadLinux(){}

  public:

    inline void		joinThread()
    {
      pthread_join(this->thread_, NULL);
    }

    inline void		cancelThread()
    {
      pthread_cancel(this->thread_);
    }

    inline void		exitThread()
    {
      pthread_exit(NULL);
    }

  };

  struct Thread : ThreadLinux
  {
    template	<typename T, typename U>
    Thread(T (*routine)(U), U arg) : ThreadLinux(routine, arg){}
  };

};

#endif
