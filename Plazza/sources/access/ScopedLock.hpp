//
// ScopedLock.hh for ScopedLock in /home/benram_s//Desktop/program/TP/threads/ex_3
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Sat Apr  2 23:44:13 2011 soufien benramdhane
// Last update Tue Apr 12 23:52:29 2011 chanh allaux
//

#ifndef			__SCOPEDLOCK_HH__
# define		__SCOPEDLOCK_HH__

#include		<iostream>
#include		"IMutex.hh"

class			ScopedLock
{
  IMutex		*_mutex;

public:
  ScopedLock(IMutex *mutex) :
    _mutex(mutex)
  {
    this->_mutex->lock();
  }

  ~ScopedLock()
  {
    this->_mutex->unlock();
  }

private: // Empecher la copie pour eviter des couilles sur le Mutex.
  ScopedLock(ScopedLock const &);
  ScopedLock&	operator=(ScopedLock const &);
};

#endif			/* ! __SCOPEDLOCK_HH__ */
