#ifndef		IMUTEX_HPP
#define		IMUTEX_HPP

/**
 * \file	IMutex.hpp
 * \author	RENAUD. J.
 * \date	July 13, 2011
 * \version	1.0
 * \brief	Interface for Mutex
 * \namespace	Thread
 */

namespace	Thread
{

  /**
   * \class		IMutex
   */

  class			IMutex
  {

  public:

    virtual		~IMutex(){}

    /**
     * \fn	virtual void	lockMutex()
     * \brief	lock a mutex
     */

    virtual void	lockMutex() = 0;

    /**
     * \fn	virtual void	unlockMutex()
     * \brief	unlock a mutex
     */

    virtual void	unlockMutex() = 0;

    /**
     * \fn	virtual void	trylockMutex()
     * \brief	try to lock a mutex
     */

    virtual bool	trylockMutex() = 0;

  };

};

#endif
