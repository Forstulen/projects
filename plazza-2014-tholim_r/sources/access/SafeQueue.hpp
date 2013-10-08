//
// SafeQueue.hh for SafeQueue in /home/benram_s//Desktop/program/TP/threads/ex_5
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Tue Apr  5 12:30:21 2011 soufien benramdhane
// Last update Wed Apr 13 22:49:56 2011 soufien benramdhane
//

#ifndef			__SAFEQUEUE_HH__
# define		__SAFEQUEUE_HH__

# include		<queue>
# include		"ScopedLock.hpp"
# include		"Mutex.hh"
# include		"ISafeQueue.hh"
# include		"CondVar.hpp"
# include		"systemError.hh"

template <typename T>
class			SafeQueue : public ISafeQueue
{
  std::queue<T>		_queue;
  Mutex			_mutex;
  bool			_isFinished;
  CondVar		*_cond;

public:
  virtual		~SafeQueue()
  {
    delete this->_cond;
  }

  SafeQueue()
    : _isFinished(false)
  {
    this->_cond = new CondVar(&this->_mutex);
  }

public:
  void			push(T value)
  {
    ScopedLock		lock(&(this->_mutex));

    this->_queue.push(value);
    this->_cond->broadcast();
  }

  bool			tryPop(T* value)
  {
    ScopedLock		lock(&(this->_mutex));
    bool			isEmpty;

    if (!(isEmpty = this->_queue.empty()))
      {
	*value = this->_queue.front();
	this->_queue.pop();
      }
    return (!isEmpty);
  }

  T			pop(void)
  {
    ScopedLock		lock(&(this->_mutex));
    T			ret;

    if (this->_queue.empty())
      {
	if (this->isFinished())
	  throw (exceptionPlazza::systemError(exceptionPlazza::POP));
	this->_cond->wait();
      }
    ret = this->_queue.front();
    this->_queue.pop();
    return (ret);
  }

  bool			empty(void) const
  {
    return (this->_queue.empty());
  }

  void			setFinished(void)
  {
    this->_isFinished = true;
  }

  bool			isFinished(void) const
  {
    if (this->_queue.empty() && this->_isFinished)
      return (true);
    return (false);
  }

};

#endif
