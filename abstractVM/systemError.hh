//
// system_error.hh for system_error in /home/benram_s//Desktop/abstractvm-2014-tholim_r/abstractVM
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Tue Feb 15 00:51:30 2011 soufien benramdhane
// Last update Sun Feb 20 14:41:21 2011 soufien benramdhane
//

#ifndef		__SYSTEMERROR_HH__
# define	__SYSTEMERROR_HH__

# include	<string>
# include	<map>
# include	<stdexcept>

enum		error_code
  {
    POP = 0,
    ASSERT,
    PRINT,
    CREAT,
    WFILE,
    WEXT,
    INSTR,
    EXIT,
    MISSARG,
    BADARG,
    BADTYPE,
    MANYARG,
    BADSYNTAX,
    USAGE,
    UNDOVER,
    DIV0,
    UNKN,
    NOTVAL,
    WMOD
  };

class				systemError: public std::exception
{
  std::string			msg;
  std::map<int, std::string>	msgType;
  unsigned int			_line;
  enum error_code		_errCode;

public:
  ~systemError () throw() {}
  systemError(enum error_code errCode, unsigned int line = 0);

public:
  const char *	what() const throw()
  { return (msg.c_str()); }
  const std::string& justMsg(enum error_code errCode);
  unsigned int getLine() const { return this->_line; }
  enum error_code	getType() const;
};

#endif		/* !__SYSTEM_ERROR_HH__ */
