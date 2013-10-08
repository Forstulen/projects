//
// Instruction.cpp for Instruction in /home/tholim_r//abstractvm-2014-tholim_r/abstractVM
// 
// Made by romain tholimet
// Login   <tholim_r@epitech.net>
// 
// Started on  Wed Feb 16 18:31:21 2011 romain tholimet
// Last update Sun Feb 20 15:45:33 2011 soufien benramdhane
//

#include			"Instruction.hh"


Instruction::Instruction(unsigned int line)
  :_name(";;"),
   _value(""),
   _type(NONE),
   _line(line)
{
}

Instruction::~Instruction()
{
}

const std::string&	Instruction::getName() const
{
  return this->_name;
}

const std::string&	Instruction::getValue() const
{
  return this->_value;
}

eOperandType		Instruction::getType() const
{
  return this->_type;
}

unsigned int		Instruction::getLine() const
{
  return this->_line;
}

void			Instruction::setName(const std::string & name)
{
  this->_name = name;
}

void			Instruction::setValue(const std::string & value)
{
  this->_value = value;
}

void			Instruction::setType(eOperandType type)
{
  this->_type = type;
}
