/**
 * \file	MutexLinux.cpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \brief	Mutex for Linux
 * \namespace	Thread
 */

#include	<iostream>
#include	"Mutex.hpp"

Thread::MutexLinux::MutexLinux()
{
  if (pthread_mutex_init(&(this->mutex_), NULL) != 0)
    std::cerr << "Mutex init fail" << std::endl;
}

Thread::MutexLinux::~MutexLinux()
{
  if (pthread_mutex_destroy(&(this->mutex_)) != 0)
    std::cerr << "Mutex destroy fail" << std::endl;
}

inline void	Thread::MutexLinux::lockMutex()
{
  if (pthread_mutex_lock(&(this->mutex_)))
    std::cerr << "Mutex lock fail" << std::endl;
}

inline void	Thread::MutexLinux::unlockMutex()
{
  if (pthread_mutex_unlock(&(this->mutex_)))
    std::cerr << "Mutex unlock fail" << std::endl;
}

inline bool	Thread::MutexLinux::trylockMutex()
{
  return (pthread_mutex_trylock(&(this->mutex_)) == 0);
}

inline pthread_mutex_t&	Thread::MutexLinux::getMutex()
{
  return this->mutex_;
}
