//
// Machine.hh for Machine in /home/benram_s//Desktop/abstractvm-2014-tholim_r/abstractVM
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Mon Feb 14 15:38:59 2011 soufien benramdhane
// Last update Sun Feb 20 16:26:33 2011 soufien benramdhane
//

#ifndef		__MACHINE_HH__
# define	__MACHINE_HH__

# include	<string>
# include	<stack>
# include	<list>
# include	<queue>
# include	<fstream>
# include	<istream>
# include	<map>

# include	"IOperand.hh"
# include	"Instruction.hh"

class				Machine
{
  std::stack<IOperand*>		_operand;
  bool				is_file;
  bool				is_exit;
  unsigned int			count;

//Typedef pour les map
  typedef void		(Machine::*ptr_func)();
  typedef std::map<const std::string, bool>		all_instructions;
  typedef std::map<const std::string, eOperandType>	all_values;
  typedef std::queue<Instruction*>			instr_queue;
//-----------------------------------------------------------------------

private:
  all_instructions		is_instruction;
  all_values			is_value;
  std::map<const std::string, ptr_func>	no_arg;
  instr_queue			waiting_instr;

  // Canonique form.
public:
  Machine(const bool);
  ~Machine();

public:
  unsigned int		getLine() const;
  instr_queue		getInstructionMap() const;

public:
  void			run(std::istream&);
  void			cleanUp();

private:
  // const or not when we change the stack?
  void			push(IOperand* other);
  void			pop();
  void			dump();
  void			assert(const IOperand& ) const;
  void			print() const;

private:
  IOperand*		getOperand();
  void			add();
  void			sub();
  void			mul();
  void			div();
  void			mod();

private:
  bool			checkFirstElem(const std::string&, Instruction*);
  void			checkSecondElem(const std::string&, const std::string&, bool, Instruction*);
  bool			checkThirdElem(const std::string&);

private: //Methodes pour le lexer
  static void		is_in_base(const char str);
  static void		is_good_format_value(const std::string&);
  const std::string	remove_comment(const std::string &);
  void			setInstructionValue(Instruction*, const std::string&);
  bool			checkInstruction_file(const std::string &);
  bool			checkInstruction_input(const std::string &);
  bool			setInstruction(const std::string &);
};

#endif		/* !__MACHINE_HH__ */
