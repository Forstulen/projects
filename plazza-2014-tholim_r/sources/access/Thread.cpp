//
// Thread.cpp for plazza in /home/tholim_r//plazza-2014-tholim_r/sources/access
//
// Made by romain tholimet
// Login   <tholim_r@epitech.net>
//
// Started on  Tue Apr 12 11:48:40 2011 romain tholimet
// Last update Sun Apr 17 18:47:08 2011 romain tholimet
//

#include		<iostream>
#include		"systemError.hh"
#include		"Thread.hh"

Thread::Thread::Thread()
  :_status(SLEEPING)
{
}

Thread::Thread::~Thread()
{
}

int			Thread::Thread::Create(func fun, void *arg)
{
  int			ret = 0;

  this->_status = RUNNING;
  ret = pthread_create(&(this->_thread), NULL, fun, arg);
  if (ret)
    {
      this->_status = SLEEPING;
      throw (exceptionPlazza::systemError(exceptionPlazza::CREATTHR));
    }
  return (ret);
}

int			Thread::Thread::Join(void **return_value)
{
  int			ret = 0;

  ret = pthread_join(this->_thread, return_value);
  if (ret)
    throw (exceptionPlazza::systemError(exceptionPlazza::JOINTHR));
  this->_status = SLEEPING;
  return (ret);
}

void			Thread::Thread::Exit(void *value_handler)
{
  if (this->_status == RUNNING)
    {
      this->_status = DEAD;
      pthread_exit(value_handler);
    }
  else
    std::cerr << "Error: There's no thread running." << std::endl;
}

int			Thread::Thread::Cancel()
{
  int			ret = 0;

  if (this->_status == RUNNING)
    {
      this->_status = DEAD;
      ret = pthread_cancel(this->_thread);
    }
  if (ret)
    std::cerr << "Error: Thread cancel failed." << std::endl;
  return (ret);
}

Thread::e_threadStatus	Thread::Thread::getStatus() const
{
  return (this->_status);
}

void			Thread::Thread::setStatus(e_threadStatus status)
{
  this->_status = status;
}
