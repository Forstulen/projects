#ifndef		TIMEREXCEPTION_HPP
# define	TIMEREXCEPTION_HPP

#include	"Exception.hpp"

class		TimerException : public Exception
{

public:

  TimerException(std::string const &wa)
    : Exception("TIMER", wa){}

  virtual ~TimerException() throw(){}

};

#endif
