//
// CondVar.hpp for CondVar in /home/benram_s//Desktop/program/TP/threads/ex_7
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Tue Apr  5 21:53:43 2011 soufien benramdhane
// Last update Sun Apr 17 18:41:22 2011 romain tholimet
//

#ifndef			__CONDVAR_HPP__
# define		__CONDVAR_HPP__

# include		<pthread.h>
# include		<iostream>

# include		"ICondVar.hh"
# include		"IMutex.hh"
# include		"Mutex.hh"
# include		"systemError.hh"

class			CondVar : public ICondVar
{
  pthread_cond_t	_cond;
  Mutex			*_mutex;
  bool			_modeMutex;

public:
  CondVar(Mutex *mutex) :
    _mutex(mutex), _modeMutex(false)
  {
    if (pthread_cond_init(&this->_cond, NULL))
      throw (exceptionPlazza::systemError(exceptionPlazza::CONDINIT));
  }

  CondVar() :
    _modeMutex(true)
  {
    if (pthread_cond_init(&this->_cond, NULL))
      throw (exceptionPlazza::systemError(exceptionPlazza::CONDINIT));
    this->_mutex = new Mutex;
  }

  virtual ~CondVar()
  {
    if (pthread_cond_destroy(&this->_cond))
      throw (exceptionPlazza::systemError(exceptionPlazza::CONDDEST));
    if (this->_modeMutex)
      delete this->_mutex;
  }

public:
  void			wait(void)
  {
    if (pthread_cond_wait(&this->_cond, this->_mutex->getMutex()))
      throw (exceptionPlazza::systemError(exceptionPlazza::CONDWAIT));
  }

  int			timedwait(int msec)
  {
    int			ret;
    struct timespec	time;

    if (clock_gettime(CLOCK_REALTIME, &time) == -1)
      throw (exceptionPlazza::systemError(exceptionPlazza::CLOCK));
    time.tv_sec += (msec / 1000);
    time.tv_nsec += (msec % 1000) * 1000000;
    ret = pthread_cond_timedwait(&this->_cond, this->_mutex->getMutex(), &time);
    return (ret);
  }

  void			signal(void)
  {
    if (pthread_cond_signal(&this->_cond))
      throw (exceptionPlazza::systemError(exceptionPlazza::CONDSIG));
  }

  void			broadcast(void)
  {
    if (pthread_cond_broadcast(&this->_cond))
      throw (exceptionPlazza::systemError(exceptionPlazza::CONDSIG));
  }
};

#endif		/* ! __CONDVAR_HPP__ */
