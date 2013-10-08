//
// IMutex.hh for mutex in /home/benram_s//Desktop/program/TP/threads/ex_2
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Sat Apr  2 17:29:51 2011 soufien benramdhane
// Last update Tue Apr 12 11:38:30 2011 soufien benramdhane
//

#ifndef			__IMUTEX_HH__
# define		__IMUTEX_HH__

# include		<pthread.h>

class			IMutex
{
public:
  virtual ~IMutex(void) {}
  virtual void lock(void) = 0;
  virtual void unlock(void) = 0;
  virtual bool trylock(void) = 0;
  virtual pthread_mutex_t *getMutex() = 0;
};

#endif			/* ! __IMUTEX_HH__ */
