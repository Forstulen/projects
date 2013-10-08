/**
 * \file	MutexWindows.cpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \brief	Implementation of Mutex Class for Windows
 * \namespace	Thread
 */

#include	"Mutex.hpp"

Thread::MutexWindows::MutexWindows()
{
  InitializeCriticalSection(&(this->mutex_));
}

Thread::MutexWindows::~MutexWindows()
{
  DeleteCriticalSection(&(this->mutex_));
}

inline void	Thread::MutexWindows::lockMutex()
{
  EnterCriticalSection(&(this->mutex_));
}

inline void	Thread::MutexWindows::unlockMutex()
{
  LeaveCriticalSection(&(this->mutex_));
}

inline bool	Thread::MutexWindows::trylockMutex()
{
  return (TryEnterCriticalSection(&(this->mutex_)) != 0);
}
