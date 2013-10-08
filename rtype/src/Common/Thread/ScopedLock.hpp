#ifndef		SCOPEDLOCK_HPP
#define		SCOPEDLOCK_HPP

/**
 * \file	ScopedLock.hpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \namespace	Thread
 */

namespace	Thread
{

  /**
   * \class	ScopedLock
   */

  template	<typename Mutex>
  class		ScopedLock
  {

    Mutex	* const _mutex;

  public:

    ScopedLock(Mutex &m): _mutex(&m)
    {
      this->_mutex->lockMutex();
    }

    ~ScopedLock()
    {
      this->_mutex->unlockMutex();
    }

  };

};

#endif
