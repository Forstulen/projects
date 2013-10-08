//
// create.hh for create in /home/benram_s//Desktop/abstractvm-2014-tholim_r/abstractVM
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Tue Feb 15 17:26:46 2011 soufien benramdhane
// Last update Sun Feb 20 15:43:09 2011 soufien benramdhane
//

#ifndef		__CREATE_HH__
# define	__CREATE_HH__

#include	<iostream>
#include	<map>
# include	<string>
# include	"IOperand.hh"

class		Create
{
private:
  Create() {}
public:
  ~Create() {}
  static Create*	createFactory();
  IOperand*		createOperand(eOperandType type, const std::string & value) const;

private:
  IOperand*		createNone(const std::string&	value) const;
  IOperand*		createInt8(const std::string&	value) const;
  IOperand*		createInt16(const std::string&	value) const;
  IOperand*		createInt32(const std::string&	value) const;
  IOperand*		createFloat(const std::string&	value) const;
  IOperand*		createDouble(const std::string& value) const;

private:
  static std::string	epur_string(const std::string& value, eOperandType type);
};

#endif	/*	!__CREATE_HH__ */
