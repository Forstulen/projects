//
// Instruction.hh for Instruction in /home/tholim_r//abstractvm-2014-tholim_r/abstractVM
// 
// Made by romain tholimet
// Login   <tholim_r@epitech.net>
// 
// Started on  Wed Feb 16 18:31:31 2011 romain tholimet
// Last update Sun Feb 20 15:45:48 2011 soufien benramdhane
//


#ifndef				__INSTRUCTION_HH__
#define				__INSTRUCTION_HH__

#include			<string>
#include			"IOperand.hh"

class				Instruction
{
  std::string			_name;
  std::string			_value;
  eOperandType			_type;
  unsigned int			_line;

public:
  Instruction(unsigned int);
  ~Instruction();

public:
  const std::string&		getName() const;
  const std::string&		getValue() const;
  eOperandType			getType() const;
  unsigned int			getLine() const;

public:
  void				setName(const std::string &);
  void				setValue(const std::string &);
  void				setType(eOperandType);
};

#endif			/*	__INSTRUCTION_HH__	*/
