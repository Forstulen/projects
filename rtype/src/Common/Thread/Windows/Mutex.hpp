#ifndef		MUTEXWINDOWS_HPP
#define		MUTEXWINDOWS_HPP

#include	<WinSock2.h>
#include	<windows.h>
#include	"IMutex.hpp"

/**
 * \file	MutexWindows.hpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \brief	Mutex Class for Windows
 * \namespace	Thread
 */

namespace	Thread
{

  /**
   * \class		MutexWindows
   */

  class			MutexWindows : public IMutex
  {

    CRITICAL_SECTION	mutex_;

  public:

    MutexWindows();
    virtual		~MutexWindows();

    inline void		lockMutex();
    inline void		unlockMutex();
    inline bool		trylockMutex();

  };

  typedef MutexWindows	Mutex;

};

#endif
