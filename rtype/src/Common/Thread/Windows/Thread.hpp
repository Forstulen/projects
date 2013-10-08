#ifndef		THREADWINDOWS_HPP
#define		THREADWINDOWS_HPP

#include	<WinSock2.h>
#include	<windows.h>
#include	"IThread.hpp"

/**
 * \file	ThreadWindows.hpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \brief	Thread for Windows
 * \namespace	Thread
 */

namespace	Thread
{

  /**
   * \class		ThreadWindows
   */

  class			ThreadWindows : public IThread
  {
    HANDLE		thread_;

  public:

    template		<typename T, typename U>
    ThreadWindows(T (*routine)(U), U arg)
      : thread_(CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(routine), arg, 0, NULL))
    {
    }

    virtual ~ThreadWindows()
    {
      this->cancelThread();
    }

  public:

    inline void		joinThread()
    {
      WaitForSingleObject(this->thread_, INFINITE);
    }

    inline void		cancelThread()
    {
      TerminateThread(this->thread_, 0);
    }

    inline void		exitThread()
    {
      ExitThread(0);
    }

  };

  struct Thread : ThreadWindows
  {
    template	<typename T, typename U>
    Thread(T (*routine)(U), U arg) : ThreadWindows(routine, arg){}
  };

};

#endif
