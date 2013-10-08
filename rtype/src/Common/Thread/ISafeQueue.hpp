#ifndef		ISAFEQUEUE_HPP
#define		ISAFEQUEUE_HPP

/**
 * \file	ISafeQueue.hpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \brief	Interface for a SafeQueue
 * \namespace	Thread
 */

namespace	Thread
{

  /**
   * \class		ISafeQueue
   */

  template		<typename Value>
  class			ISafeQueue
  {

  public:

    virtual		~ISafeQueue(){}

    /**
     * \fn	virtual void	push(Value const&)
     * \brief	Insert a value in the SafeQueue
     */

    virtual void	push(Value const &) = 0;

    /**
     * \fn	virtual void	pop()
     * \brief	Get a value from the SafeQueue
     */

    virtual bool	pop(Value &) = 0;

    virtual bool	top(Value &) = 0;

    /**
     * \fn	virtual bool	isFinished()
     * \brief	SafeQueue work is done
     *
     * The work is finished when setFinished was called
     * and there are no more Values in the SafeQueue.
     */

    virtual bool	isFinished() const = 0;

    /**
     * \fn	virtual bool	setFinished()
     * \brief	set the end of the work
     *
     * If there are some value in the Safequeue it will
     * continue unless there are some Values.
     */

    virtual void	setFinished() = 0;

  };

};

#endif
