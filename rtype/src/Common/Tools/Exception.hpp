#ifndef		EXCEPTION_HPP
#define		EXCEPTION_HPP

#include	<string>
#include	<exception>
#include	<ostream>

class		Exception : public std::exception
{

  std::string	where_;
  std::string	what_;

public:

  Exception(std::string const &where, std::string const &what)
    : where_(where.c_str()), what_(what.c_str()){}

  virtual ~Exception() throw() {}

  const char * what () const throw (){ return this->what_.c_str(); }
  const char * where() const throw (){ return this->where_.c_str();}

};

std::ostream&	operator << (std::ostream& os, Exception const &e);


#endif
