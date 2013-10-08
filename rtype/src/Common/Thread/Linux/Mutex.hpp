#ifndef		MUTEXLINUX_HPP
#define		MUTEXLINUX_HPP

#include	<pthread.h>
#include	"IMutex.hpp"

/**
 * \file	MutexLinux.hpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \brief	Mutex Class for Linux
 * \namespace	Thread
 */

namespace	Thread
{

  /**
   * \class			MutexLinux
   */

  class				MutexLinux : public IMutex
  {

    pthread_mutex_t		mutex_;

  public:

    MutexLinux();
    virtual			~MutexLinux();

    void			lockMutex();
    void			unlockMutex();
    bool			trylockMutex();
    pthread_mutex_t&		getMutex();

  };

  typedef MutexLinux		Mutex;

};

#endif
