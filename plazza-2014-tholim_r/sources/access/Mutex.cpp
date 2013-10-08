//
// Mutex.cpp for Mutex in /home/benram_s//Desktop/program/TP/threads/ex_2
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Sat Apr  2 17:33:47 2011 soufien benramdhane
// Last update Sun Apr 17 18:43:38 2011 romain tholimet
//

#include		<iostream>
#include		"Mutex.hh"
#include		"systemError.hh"

Mutex::Mutex()
{
  if (pthread_mutex_init(&(this->_mutex), NULL) != 0)
    throw (exceptionPlazza::systemError(exceptionPlazza::MUTINIT));
}

Mutex::~Mutex()
{
  if (pthread_mutex_destroy(&(this->_mutex)) != 0)
    throw (exceptionPlazza::systemError(exceptionPlazza::MUTDEST));
}

//----------------------------------------------------------------------------

void			Mutex::lock()
{
  if (pthread_mutex_lock(&(this->_mutex)))
    throw (exceptionPlazza::systemError(exceptionPlazza::MUTLOCK));
}

void			Mutex::unlock()
{
  if (pthread_mutex_unlock(&(this->_mutex)))
    throw (exceptionPlazza::systemError(exceptionPlazza::MUTUNLOCK));
}

bool			Mutex::trylock()
{
  return (pthread_mutex_trylock(&(this->_mutex)));
}

pthread_mutex_t		*Mutex::getMutex()
{
  return (reinterpret_cast<pthread_mutex_t *>(&this->_mutex));
}
