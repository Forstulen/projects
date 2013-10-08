//
// systemError.cpp for systemError in /home/benram_s//Desktop/abstractvm-2014-tholim_r/abstractVM
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Tue Feb 15 00:59:05 2011 soufien benramdhane
// Last update Sun Feb 20 17:16:17 2011 soufien benramdhane
//

#include	<string>

#include	"systemError.hh"

systemError::systemError(enum error_code errCode, unsigned int line)
  :_line(line), _errCode(errCode)
{
  this->msgType[POP] = "The Stack is empty... You can't pop a value.";
  this->msgType[ASSERT] = "The front value of the stack is different to this value.";
  this->msgType[PRINT] = "The number you are trying to print is not an 8 bits integer.";
  this->msgType[CREAT] = "Wrong Operand Type.";
  this->msgType[WFILE] = "No such file.";
  this->msgType[WEXT] = "Bad file type (.avm). ";
  this->msgType[INSTR] = "No such instruction.";
  this->msgType[EXIT] = "No 'exit' instruction.";
  this->msgType[MISSARG] = "Missing an argument.";
  this->msgType[BADARG] = "Bad argument.";
  this->msgType[BADTYPE] = "Bad type.";
  this->msgType[MANYARG] = "Too many arguments.";
  this->msgType[BADSYNTAX] = "Missing parenthesis.";
  this->msgType[USAGE] = "Usage: ./avm [file_name]";
  this->msgType[UNDOVER] = "Overflow / Underflow in this operation.";
  this->msgType[DIV0] = "Division by zero.";
  this->msgType[UNKN] = "This parameter is not a number.";
  this->msgType[NOTVAL] = "There is no value for this instruction (NULL).";
  this->msgType[WMOD] = "Cannot use modulo operator on float or double.";
  this->msg = justMsg(errCode);
}

const std::string&	systemError::justMsg(enum error_code errCode)
{
  return (this->msgType[errCode]);
}

enum error_code		systemError::getType() const
{
  return (this->_errCode);
}
