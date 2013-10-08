/*
** Machine.c for Machine in /home/benram_s//Desktop/abstractvm-2014-tholim_r/abstractVM
** 
** Made by soufien benramdhane
** Login   <benram_s@epitech.net>
** 
** Started on  Mon Feb 14 15:41:47 2011 soufien benramdhane
// Last update Sun Feb 20 17:20:05 2011 soufien benramdhane
*/

#include	<iostream>
#include	<fstream>
#include	<sstream>
#include	<string>
#include	<vector>
#include	<algorithm>

#include	"create.hh"
#include	"Machine.hh"
#include	"systemError.hh"
#include	"Operand.hpp"

Machine::Machine(const bool t):
  is_file(t), is_exit(false), count(0)
{
  no_arg["pop"] = &Machine::pop;
  no_arg["dump"] = &Machine::dump;
  no_arg["add"] = &Machine::add;
  no_arg["sub"] = &Machine::sub;
  no_arg["mul"] = &Machine::mul;
  no_arg["div"] = &Machine::div;
  no_arg["mod"] = &Machine::mod;

  //Map pour la gestion des arguments
  is_instruction["push"] = true;
  is_instruction["pop"] = false;
  is_instruction["dump"] = false;
  is_instruction["assert"] = true;
  is_instruction["add"] = false;
  is_instruction["sub"] = false;
  is_instruction["mul"] = false;
  is_instruction["div"] = false;
  is_instruction["mod"] = false;
  is_instruction["print"] = false;
  is_instruction["exit"] = false;
  //Map pour la gestion de l'enum
  is_value["int8"] = INT8;
  is_value["int16"] = INT16;
  is_value["int32"] = INT32;
  is_value["float"] = FLOAT;
  is_value["double"] = DOUBLE;
}

Machine::~Machine()
{
  IOperand*		op;
  Instruction*		inst;

  while (this->_operand.empty() == false)
    {
      op = this->_operand.top();
      this->_operand.pop();
      delete op;
    }
  while (this->waiting_instr.empty())
    {
      inst = this->waiting_instr.front();
      this->waiting_instr.pop();
      delete inst;
    }
}

//------------------------------AVM_ACTIONS-----------------------------------

void				Machine::push(IOperand* other)
{
  Operand<int>			check(other->getType(), "");
  std::stringstream		ss;
  long double			nb;

  ss << other->toString();
  ss >> nb;
  if ((check.overflow[other->getType()] < nb)
      || (check.underflow[other->getType()] > nb))
    throw systemError(UNDOVER, this->count);
  this->_operand.push(other);
}

void				Machine::pop()
{
  IOperand*		op;

  if (this->_operand.empty() == true)
    throw systemError(POP, this->count);
  op = this->_operand.top();
  this->_operand.pop();
  delete op;
}

void				Machine::dump()
{
  std::stack<IOperand*>		tmp;
  IOperand*			node;

  std::cout << "Stack Dump:" << std::endl;
  while (!this->_operand.empty())
    {
      node = this->_operand.top();
      std::cout << node->toString() << std::endl;
      tmp.push(node);
      this->_operand.pop();
    }
  while (!tmp.empty())
    {
      node = tmp.top();
      this->_operand.push(node);
      tmp.pop();
    }
}

void				Machine::assert(const IOperand& other) const
{
  double			top;
  double			oth;
  IOperand*			other_op;
  std::stringstream		ss;
  std::stringstream		iss;

  if (this->_operand.empty() == true)
    throw systemError(POP, this->count);
  other_op = this->_operand.top();
  ss << other_op->toString();
  ss >> top;
  iss << other.toString();
  iss >> oth;
  if ((top != oth) || (other_op->getType() != other.getType()))
    throw systemError(ASSERT, this->count);
}

void				Machine::print() const
{
  std::stringstream		ss;
  int				c;

  if (this->_operand.empty() == true)
    throw systemError(POP, this->count);
  if (this->_operand.top()->getType() == INT8)
    {
      ss << this->_operand.top()->toString();
      ss >> c;
      std::cout << (char)c << std::endl;
    }
  else
    throw systemError(PRINT, this->count);
}

//-------------------------------OPERATION-----------------------------------

IOperand*			Machine::getOperand()
{
  IOperand*		op;

  if (this->_operand.empty() == true)
    throw systemError(POP, this->count);
  op = this->_operand.top();
  this->_operand.pop();
  return (op);
}

void				Machine::add()
{
  IOperand*		op1;
  IOperand*		op2;

  op1 = this->getOperand();
  op2 = this->getOperand();
  this->push((*op1) + (*op2));
  delete op1;
  delete op2;
}

void				Machine::sub()
{
  IOperand*		op1;
  IOperand*		op2;

  op1 = this->getOperand();
  op2 = this->getOperand();
  this->_operand.push((*op1) - (*op2));
  delete op1;
  delete op2;
}

void				Machine::mul()
{
  IOperand*		op1;
  IOperand*		op2;

  op1 = this->getOperand();
  op2 = this->getOperand();
  this->_operand.push((*op1) * (*op2));
  delete op1;
  delete op2;
}

void				Machine::div()
{
  IOperand*		op1;
  IOperand*		op2;

  op1 = this->getOperand();
  op2 = this->getOperand();
  this->_operand.push((*op1) / (*op2));
  delete op1;
  delete op2;
}

void				Machine::mod()
{
  IOperand*		op1;
  IOperand*		op2;

  op1 = this->getOperand();
  op2 = this->getOperand();
  this->_operand.push((*op1) % (*op2));
  delete op1;
  delete op2;
}

//------------------------------------------------------------------------------------

void				Machine::cleanUp()
{
  Instruction*			inst;
  IOperand*			op;

  while (!(this->waiting_instr.empty()))
    {
      inst = this->waiting_instr.front();
      this->waiting_instr.pop();
      delete inst;
    }
  while (!(this->_operand.empty()))
    {
      op = this->_operand.top();
      this->_operand.pop();
      delete op;
    }
}

void				Machine::run(std::istream& flux)
{
  std::string			buf;
  Instruction*			inst;
  IOperand*			op;
  Create*			creaOp = Create::createFactory();
  std::map<const std::string, ptr_func>::iterator	it;

  while (std::getline(flux, buf))
    if (this->setInstruction(buf))
      break;
  while (!this->waiting_instr.empty() && (this->waiting_instr.front())->getName() != "exit")
    {
      inst = this->waiting_instr.front();
      if ((it = this->no_arg.find(inst->getName())) == no_arg.end())
	{
	  op = creaOp->createOperand(inst->getType(), inst->getValue());
	  if (inst->getName() == "push")
	    this->push(op);
	  else if (inst->getName() == "print")
	    this->print();
	  else
	    {
	      this->assert(*op);
	      delete op;
	    }
	}
      else
	(this->*no_arg[inst->getName()])();
      this->waiting_instr.pop();
      delete inst;
    }
  delete creaOp;
}

//-----------------------------------------------------------------------------

void				Machine::is_in_base(const char c)
{
  if ((c < '0' || c > '9') && (c != '.') && (c != '-'))
    throw systemError(UNKN);
}

void				Machine::is_good_format_value(const std::string& value)
{
  if ((value.find_first_of('.') != value.find_last_of('.')) ||
      (value.find_first_of('-') != value.find_last_of('-')) ||
      (value.find_first_of('-') != 0 && value.find_first_of('-') != std::string::npos))
    throw systemError(UNKN);
}

//----------------------------------------------------------------------------

const std::string		Machine::remove_comment(const std::string & instruction)
{
  std::string			rm_comment(instruction);
  unsigned int                  pos_comment = instruction.find(";");
  unsigned int                  pos_eof;

  if (pos_comment != std::string::npos)
    {
      if (this->is_file == false
	  && (pos_eof = instruction.find(";", pos_comment + 1)) != std::string::npos)
        {
          if (pos_eof == pos_comment + 1)
            rm_comment = instruction.substr(0, pos_eof + 1);
        }
      else
	rm_comment = instruction.substr(0, pos_comment);
    }
  return rm_comment;
}

void				Machine::setInstructionValue(Instruction* new_instruction, const std::string& str)
{
  std::string			type;
  std::string			value(new_instruction->getValue().c_str());
  all_values::iterator		it;
  std::string::iterator		end;
  unsigned int			first_parenthesis = str.find("(");
  unsigned int			last_parenthesis = str.find(")");

  if (first_parenthesis == std::string::npos || last_parenthesis == std::string::npos)
    throw systemError(BADSYNTAX, this->count);
  type = str.substr(0, first_parenthesis);
  if ((it = is_value.find(type)) == is_value.end())
    throw systemError(BADTYPE, this->count);
  new_instruction->setType((*it).second);
  new_instruction->setValue(str.substr(first_parenthesis + 1, last_parenthesis - first_parenthesis - 1));
  if (new_instruction->getValue() == "")
    throw systemError(NOTVAL);
  end = value.end();
  for_each(value.begin(), end, &Machine::is_in_base);
  is_good_format_value(new_instruction->getValue());
}

bool			Machine::checkInstruction_file(const std::string& instruction)
{
  Instruction*			new_instruction = new Instruction(this->count);
  std::stringstream		ss;
  all_instructions::iterator	it;
  std::vector<std::string>	elements;
  unsigned int			i = 0;

  ss << this->remove_comment(instruction);
  while (ss)
    {
      elements.push_back("");
      ss >> elements[i];
      ++i;
    }
  if (i > 1)
    {
      if ((it = this->is_instruction.find(elements[0])) == this->is_instruction.end())
	throw systemError(INSTR, this->count);
    }
  else
    {
      delete new_instruction;
      return false;
    }
  if (elements[0] == "exit")
    this->is_exit = true;
  new_instruction->setName(elements[0]);
  if ((*it).second)
    {
      if (i == 3)
	this->setInstructionValue(new_instruction, elements[1]);
      else if (i == 2)
	throw systemError(MISSARG, this->count);
      else
	throw systemError(MANYARG, this->count);
    }
  else if (i > 2)
    throw systemError(MANYARG, this->count);
  this->waiting_instr.push(new_instruction);
  return false;
}


bool			Machine::checkFirstElem(const std::string& element, Instruction* new_instruction)
{
  all_instructions::iterator	it;

  if (element == ";;")
    {
      delete new_instruction;
      if (this->is_exit)
	return true;
      throw systemError(EXIT, this->count);
    }
  else if ((it = this->is_instruction.find(element)) == this->is_instruction.end())
    throw systemError(INSTR, this->count);
  return false;
}

void			Machine::checkSecondElem(const std::string& firstElem, const std::string& element,
						 bool arg, Instruction* new_instruction)
{
  if (arg)
    {
      if (element == ";;")
	throw systemError(MISSARG, this->count);
      this->setInstructionValue(new_instruction, element);
    }
  else if (element == ";;")
    {
      if (firstElem == "exit")
	this->is_exit = true;
      if (!this->is_exit)
	throw systemError(EXIT, this->count);
    }
  else
    throw systemError(MANYARG, this->count);
}

bool			Machine::checkThirdElem(const std::string& elem)
{
  if (elem == ";;")
    {
      if (this->is_exit)
	return true;
      throw systemError(EXIT, this->count);
    }
  else
    throw systemError(MANYARG, this->count);
  return false;
}


bool			Machine::checkInstruction_input(const std::string & instruction)
{
  Instruction*			new_instruction = new Instruction(this->count);
  std::stringstream		ss;
  all_instructions::iterator	it;
  std::vector<std::string>	elements;
  unsigned int			i = 0;
  std::string			tmp;

  ss << remove_comment(instruction);
  if (instruction.find(";;") != std::string::npos)
    {
      while (ss)
	{
	  elements.push_back("");
	  ss >> elements[i];
	  ++i;
	}
      if (this->checkFirstElem(elements[0], new_instruction))
	return true;
      it = is_instruction.find(elements[0]);
      new_instruction->setName(elements[0]);
      this->waiting_instr.push(new_instruction);
      this->checkSecondElem(elements[0], elements[1], (*it).second, new_instruction);
      if (this->checkThirdElem(elements[2]))
	return true;
    }
  else
    {
      delete new_instruction;
      return this->checkInstruction_file(instruction);
    }
  return false;
}

bool			Machine::setInstruction(const std::string & instruction)
{
  ++(this->count);
  if (!this->is_file)
    return this->checkInstruction_input(instruction);
  else
    return this->checkInstruction_file(instruction);
}

//----------------------------------------------------------------------------

unsigned int		Machine::getLine() const
{
  return this->count;
}

// ref ici ce serait mieu
Machine::instr_queue	Machine::getInstructionMap() const
{
  return waiting_instr;
}
