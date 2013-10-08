//
// IThread.hh for IThread in /home/benram_s//Desktop/program/TP/threads/ex_4
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Sun Apr  3 00:00:34 2011 soufien benramdhane
// Last update Sun Apr  3 00:37:58 2011 soufien benramdhane
//

#ifndef			__ITHREAD_HH__
# define		__ITHREAD_HH__

typedef void		*(*func)(void *);

class			IThread
{
public:
  virtual		~IThread() {}
  virtual int		Create(func fun, void *arg) = 0;
  virtual int		Join(void **return_value) = 0;
  virtual void		Exit(void *value_handler) = 0;
};

#endif			/* ! __ITHREAD_HH__ */
