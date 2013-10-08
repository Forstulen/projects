//
// Operand.hpp for Operand in /home/tholim_r//abstractvm-2014-tholim_r/abstractVM
// 
// Made by romain tholimet
// Login   <tholim_r@epitech.net>
// 
// Started on  Mon Feb 14 15:41:05 2011 romain tholimet
// Last update Sun Feb 20 15:38:14 2011 soufien benramdhane
//

#ifndef				__OPERAND_HPP__
#define				__OPERAND_HPP__

#include			<iostream>
#include			<sstream>
#include			<map>
#include			<cmath>
#include			<limits>

#include			"create.hh"
#include			"IOperand.hh"
#include			"systemError.hh"

enum		eOperation
{
  ADD,
  SUB,
  MUL,
  DIV,
  MOD
};

template<typename T>
class				Operand : public IOperand
{
  typedef std::map<eOperandType, double>	map_type;
public:
  map_type					overflow;
  map_type					underflow;

private:
  T				_value;
  eOperandType			_type;
  std::string			_value_string;

public:
  Operand(eOperandType type, const std::string& value)
  :  _type(type),
     _value_string(value)
  {
    std::stringstream	tmp;
    std::stringstream	ss;

    tmp << value;
    tmp >> this->_value;

    overflow[INT8] = std::numeric_limits<char>::max();
    overflow[INT16] = std::numeric_limits<short>::max();
    overflow[INT32] = std::numeric_limits<int>::max();
    overflow[FLOAT] = std::numeric_limits<float>::max();
    overflow[DOUBLE] = std::numeric_limits<double>::max();

    underflow[INT8] = std::numeric_limits<char>::min();
    underflow[INT16] = std::numeric_limits<short>::min();
    underflow[INT32] = std::numeric_limits<int>::min();
    underflow[FLOAT] = -1 * std::numeric_limits<float>::max();
    underflow[DOUBLE] = -1 * std::numeric_limits<double>::max();
  }

  ~Operand() {}

public:
  const std::string &		toString() const
  {
    return this->_value_string;
  }

  int		                getPrecision() const
  {
    return this->_type;
  }

  eOperandType			getType() const
  {
    return this->_type;
  }


private:
  bool			check_flow(double & op1, const T & op2,
				   eOperandType type,
				   enum eOperation sign) const
  {
    if (sign == ADD && (op1 + op2) <= this->overflow[type]
    	&& (op1 + op2) >= this->underflow[type])
      return (false);
    else if (sign == SUB && (op1 - op2) <= this->overflow[type]
    	&& (op1 - op2) >= this->underflow[type])
      return (false);
    else if (sign == MUL && (op1 * op2) <= this->overflow[type]
    	&& (op1 * op2) >= this->underflow[type])
      return (false);
    else if (sign == DIV && (op1 / op2) <= this->overflow[type]
    	&& (op1 / op2) >= this->underflow[type])
      return (false);
    else if (sign == MOD && fmod(op1, op2) <= this->overflow[type]
    	&& fmod(op1, op2) >= this->underflow[type])
      return (false);
    return (true);
  }

public:
  IOperand*			operator+(const IOperand& op) const
  {
    IOperand*			new_elem;
    double			res;
    eOperandType		type;
    std::stringstream		ss;
    std::stringstream		os;
    std::string			tmp;
    Create*			factory = Create::createFactory();
    map_type::const_iterator	it_over;
    map_type::const_iterator	it_under;

    ss << op.toString();
    ss >> res;
    type = ((this->getType() < op.getType()) ? op.getType() : this->getType());
    it_over = this->overflow.find(type);
    it_under = this->underflow.find(type);
    if ((res + this->_value) > (*it_over).second
      || (res + this->_value) < (*it_under).second)
      throw systemError(UNDOVER);
    res += this->_value;
    os << res;
    os >> tmp;
    new_elem = factory->createOperand(type, tmp);
    delete factory;
    return new_elem;
  }

  IOperand*			operator-(const IOperand& op) const
  {
    IOperand*			new_elem;
    double			res;
    eOperandType		type;
    std::stringstream		ss;
    std::stringstream		os;
    std::string			tmp;
    Create*			factory = Create::createFactory();
    map_type::const_iterator	it_over;
    map_type::const_iterator	it_under;

    ss << op.toString();
    ss >> res;
    type = ((this->getType() < op.getType()) ? op.getType() : this->getType());
    it_over = this->overflow.find(type);
    it_under = this->underflow.find(type);
    if ((res - this->_value) > (*it_over).second
      || (res - this->_value) < (*it_under).second)
      throw systemError(UNDOVER);
    res -= this->_value;
    os << res;
    os >> tmp;
    new_elem = factory->createOperand(type, tmp);
    delete factory;
    return new_elem;
  }

  IOperand*			operator/(const IOperand& op) const
  {
    IOperand*			new_elem;
    double			res;
    eOperandType		type;
    std::stringstream		ss;
    std::stringstream		os;
    std::string			tmp;
    Create*			factory = Create::createFactory();
    map_type::const_iterator	it_over;
    map_type::const_iterator	it_under;

    ss << op.toString();
    ss >> res;
    if (this->_value == 0)
      throw systemError(DIV0);
    type = ((this->getType() < op.getType()) ? op.getType() : this->getType());
    it_over = this->overflow.find(type);
    it_under = this->underflow.find(type);
    if ((res / this->_value) > (*it_over).second
      || (res / this->_value) < (*it_under).second)
      throw systemError(UNDOVER);
    res /= this->_value;
    os << res;
    os >> tmp;
    new_elem = factory->createOperand(type, tmp);
    delete factory;
    return new_elem;
  }

  IOperand*			operator*(const IOperand& op) const
  {
    IOperand*			new_elem;
    double			res;
    eOperandType		type;
    std::stringstream		ss;
    std::stringstream		os;
    std::string			tmp;
    Create*			factory = Create::createFactory();
    map_type::const_iterator	it_over;
    map_type::const_iterator	it_under;

    ss << op.toString();
    ss >> res;
    if (this->_value == 0)
      throw systemError(DIV0);
    type = ((this->getType() < op.getType()) ? op.getType() : this->getType());
    it_over = this->overflow.find(type);
    it_under = this->underflow.find(type);
    if ((res * this->_value) > (*it_over).second
      || (res * this->_value) < (*it_under).second)
      throw systemError(UNDOVER);
    res *= this->_value;
    os << res;
    os >> tmp;
    new_elem = factory->createOperand(type, tmp);
    delete factory;
    return new_elem;
  }

  IOperand*			operator%(const IOperand& op) const
  {
    IOperand*			new_elem;
    double			res;
    eOperandType		type;
    std::stringstream		ss;
    std::stringstream		os;
    std::string			tmp;
    Create*			factory = Create::createFactory();
    map_type::const_iterator	it_over;
    map_type::const_iterator	it_under;

    ss << op.toString();
    ss >> res;
    type = ((this->getType() < op.getType()) ? op.getType() : this->getType());
    it_over = this->overflow.find(type);
    it_under = this->underflow.find(type);
    if ((this->getType() == FLOAT) || (this->getType() == DOUBLE)
	|| (op.getType() == FLOAT) || (op.getType() == DOUBLE))
      throw systemError(WMOD);
    if (fmod(res, this->_value) > (*it_over).second
	|| fmod(res, this->_value) < (*it_under).second)
      throw systemError(UNDOVER);
    res = fmod(res, this->_value);
    os << res;
    os >> tmp;
    new_elem = factory->createOperand(type, tmp);
    delete factory;
    return new_elem;
  }

public:
  bool				operator!=(const IOperand& op) const
  {
    double			res;
    std::stringstream		ss;
    std::string			tmp;

    ss << op.toString();
    ss >> res;
    if (this->_value != res)
      return true;
    return false;
  }
};

#endif				/*		__OPERAND_HPP__	*/
