//
// IConVar.hh for ICondVar in /home/benram_s//Desktop/program/TP/threads/ex_7
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Tue Apr  5 21:51:57 2011 soufien benramdhane
// Last update Tue Apr  5 23:19:15 2011 soufien benramdhane
//

#ifndef			__ICONDVAR_HH__
# define		__ICONDVAR_HH__

class			ICondVar
{
public:
  virtual ~ICondVar() {}
  virtual void wait(void) = 0;
  virtual void signal(void) = 0;
  virtual void broadcast(void) = 0;
};

#endif			/* ! __ICONDVAR_HH__ */
