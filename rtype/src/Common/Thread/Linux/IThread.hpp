#ifndef		ITHREAD_HPP
#define		ITHREAD_HPP

/**
 * \file	IThread.hpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \brief	Interface for Thread
 * \namespace	Thread
 */

namespace	Thread
{

  /**
   * \class		IThead
   */

  class			IThread
  {

  protected:

    typedef void	*(*start_routine)(void* arg);

  public:

    virtual		~IThread() {}

    /**
     * \fn	virtual void	joinThread()
     */

    virtual void	joinThread() = 0;

    /**
     * \fn	virtual void	cancelThread()
     */

    virtual void	cancelThread() = 0;

    /**
     * \fn	virtual void	exitThread()
     */

    virtual void	exitThread() = 0;

  };

};

#endif
