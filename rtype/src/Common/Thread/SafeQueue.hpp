#ifndef		SAFEQUEUE_HPP
#define		SAFEQUEUE_HPP

#include	<queue>

#include	"ScopedLock.hpp"
#include	"ISafeQueue.hpp"
#include	"Mutex.hpp"

/**
 * \file	SafeQueue.hpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \brief	SafeQueue with Mutex
 * \namespace	Thread
 */

namespace	Thread
{

  /**
   * \class		SafeQueue
   */

  template		<typename Value>
  class			SafeQueue : public ISafeQueue<Value>
  {

  private:

    std::queue<Value>	queue_;
    bool		end_;
    Mutex		mutex_;

  public:

    SafeQueue() : end_(false) {}
    ~SafeQueue() {}

    void		push(Value const &value)
    {
      ScopedLock<Mutex>	lock(this->mutex_);

      this->queue_.push(value);
    }

    bool		pop(Value &value)
    {
      ScopedLock<Mutex>	lock(this->mutex_);

      if (this->queue_.empty())
	return (false);
      value = this->queue_.front();
      this->queue_.pop();
      return (true);
    }

    bool	      	top(Value &value)
    {
      if (this->queue_.empty())
	return (false);
      value = this->queue_.front();
      return (true);
    }

    inline bool		isFinished() const
    {
      return (this->end_ && this->queue_.empty());
    }

    inline void		setFinished()
    {
      this->end_ = true;
    }

    inline int		size() const
    {
      return this->queue_.size();
    }
  };

};

#endif
