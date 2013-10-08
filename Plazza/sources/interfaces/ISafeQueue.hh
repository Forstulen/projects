//
// ISafeQueue.hh for ISafeQueue in /home/benram_s//Desktop/program/TP/threads/ex_5
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Tue Apr  5 12:28:50 2011 soufien benramdhane
// Last update Tue Apr  5 22:33:50 2011 soufien benramdhane
//

#ifndef			__ISAFEQUEUE_HH__
# define		__ISAFEQUEUE_HH__

/* a modifer template */

class			ISafeQueue
{
public:
  virtual ~ISafeQueue(void) {}
  virtual void push(int value) = 0;
  virtual bool tryPop(int* value) = 0;
  virtual int  pop(void) = 0;
  virtual bool isFinished(void) const = 0;
  virtual void setFinished(void) = 0;
};

#endif
