//
// Thread.hh for Thread in /home/benram_s//Desktop/program/TP/threads/ex_4
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Sun Apr  3 00:16:32 2011 soufien benramdhane
// Last update Thu Apr 14 15:24:15 2011 soufien benramdhane
//

#ifndef				__THREAD_HH__
# define			__THREAD_HH__

# include			<pthread.h>

# include			 "IThread.hh"

namespace			Thread
{
  typedef enum			e_threadStatus
    {
      SLEEPING,
      RUNNING,
      DEAD
    }				e_threadStatus;

  class				Thread : public IThread
  {
    pthread_t			_thread;
    e_threadStatus		_status;

  public:
    Thread();
    virtual ~Thread();

  public:
    int				Create(func, void *);
    int				Join(void **);
    void			Exit(void *);
    int				Cancel();
  public:
    e_threadStatus		getStatus() const;
    void			setStatus(e_threadStatus status);
  };
}
#endif			/* ! __THREAD_HH__ */
