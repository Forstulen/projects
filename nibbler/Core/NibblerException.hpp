//
// nibblerExection.hpp for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Tue Mar  8 12:28:30 2011 chanh allaux
// Last update Tue Mar  8 12:33:33 2011 chanh allaux
//

#ifndef			__EXCEPTION_H_
# define		__EXCEPTION_H_

#include		<string>

class			nibblerException : public std::exception
{
  std::string		_message;

public:
  ~nibblerException() throw() {}
  explicit nibblerException(std::string const & error) : _message(error) {}
  std::string const &	getMessage(void) const { return (this->_message); }
  const char* what() const throw() { return (_message.c_str()); }
};

#endif
