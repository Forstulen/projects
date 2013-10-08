//
// create.cpp for create in /home/benram_s//Desktop/abstractvm-2014-tholim_r/abstractVM
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Tue Feb 15 17:28:37 2011 soufien benramdhane
// Last update Sun Feb 20 18:25:08 2011 soufien benramdhane
//

#include	"Operand.hpp"
#include	"systemError.hh"

//--------------------------------CREATION_OPERAND------------------------------------

typedef		IOperand* (Create::*creaType)(const std::string& value) const;

Create*		Create::createFactory()
{
  return (new Create);
}


IOperand*	Create::createOperand(eOperandType type, const std::string & value) const
{
  std::map<eOperandType, creaType>		op;
  std::map<eOperandType, creaType>::iterator	it;

  op[NONE] = &Create::createNone;
  op[INT8] = &Create::createInt8;
  op[INT16] = &Create::createInt16;
  op[INT32] = &Create::createInt32;
  op[FLOAT] = &Create::createFloat;
  op[DOUBLE] = &Create::createDouble;
  it = op.find(type);
  if (it != op.end())
    return (this->*op[type])(value);
  else
    throw systemError(CREAT);
}

std::string			Create::epur_string(const std::string& value, eOperandType type)
{
  std::string					epur_str(value.c_str());
  std::string::iterator				it = epur_str.begin();
  unsigned int					point_pos = epur_str.find('.');

  if (*it == '.')
    epur_str = "0" + epur_str;
  while (*it == '0' && it != (epur_str.end() - 1))
    {
      if (*(it + 1) != '.')
	epur_str.erase(it);
      else
	break ;
      it = epur_str.begin();
    }
  it = epur_str.end() - 1;
  if (point_pos != std::string::npos)
    {
      if ((type == FLOAT) || (type == DOUBLE))
	while (*it == '0' && it != (epur_str.begin() + 1))
	  {
	    if (*(it - 1) != '.')
	      epur_str.erase(it);
	    else
	      break ;
	    it = epur_str.end() - 1;
	  }
      else
	epur_str = epur_str.substr(0, epur_str.find('.'));
    }
  return (epur_str);
}

IOperand*			Create::createNone(const std::string&	value) const
{
  return (new Operand<int>(NONE, value));
}

IOperand*			Create::createInt8(const std::string&	value) const
{
  return (new Operand<int>(INT8, Create::epur_string(value, INT8)));
}

IOperand*			Create::createInt16(const std::string&	value) const
{
  return (new Operand<int>(INT16, Create::epur_string(value, INT16)));
}

IOperand*			Create::createInt32(const std::string&	value) const
{
  return (new Operand<int>(INT32, Create::epur_string(value, INT32)));
}

IOperand*			Create::createFloat(const std::string&	value) const
{
  return (new Operand<float>(FLOAT, Create::epur_string(value, FLOAT)));
}

IOperand*			Create::createDouble(const std::string&value) const
{
  return (new Operand<double>(DOUBLE, Create::epur_string(value, DOUBLE)));
}
