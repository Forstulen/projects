//
// Mutex.hh for Mutex in /home/benram_s//Desktop/program/TP/threads/ex_2
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Sat Apr  2 17:31:12 2011 soufien benramdhane
// Last update Tue Apr 12 11:38:18 2011 soufien benramdhane
//

#ifndef			__MUTEX_HH__
# define		__MUTEX_HH__

# include		<pthread.h>
# include		"IMutex.hh"

class			Mutex : public IMutex
{
  pthread_mutex_t	_mutex;

public:
  virtual ~Mutex();
  Mutex();

public:
  void			lock();
  void			unlock();
  bool			trylock();
  pthread_mutex_t	*getMutex();
};

#endif			/* ! __MUTEX_HH__ */
