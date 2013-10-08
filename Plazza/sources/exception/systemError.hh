//
// systemError.hh for plazza in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r/sources/exception
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Thu Apr  7 21:07:39 2011 soufien benramdhane
// Last update Sun Apr 17 18:32:12 2011 romain tholimet
//

#ifndef		__SYSTEMERROR_HH__
# define	__SYSTEMERROR_HH__

#include	<string>
#include	<map>

namespace			exceptionPlazza
{
  typedef enum			errorCode
    {
      MKFIFO = 0,
      FOPEN,
      SEND,
      RECEIVE,
      POP,
      BADING,
      CLOCK,
      FORK,
      CONDINIT,
      CONDDEST,
      CONDWAIT,
      CONDSIG,
      MUTINIT,
      MUTDEST,
      MUTLOCK,
      MUTUNLOCK,
      CREATTHR,
      JOINTHR,
      BADARG,
      BADLIB,
      NOTLOG,
      KITCHERR
    }				errorCode;

  class				systemError: public std::exception
  {
    std::string			msg;
    std::map<int, std::string>	msgType;
    errorCode			_errCode;

  public:
    ~systemError () throw() {}
    systemError(errorCode errCode);
    systemError(std::string const &);

  public:
    const char *		what() const throw()
    { return (msg.c_str()); }
    std::string			justMsg(errorCode errCode);
    errorCode			getType();
    std::string const &		getMessage() const { return (this->msg); }
  };
}
#endif		/* !__SYSTEM_ERROR_HH__ */
