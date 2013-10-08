
//
// IOperand.hh for IOperand in /home/tholim_r//abstractvm-2014-tholim_r/abstractVM
// 
// Made by romain tholimet
// Login   <tholim_r@epitech.net>
// 
// Started on  Mon Feb 14 11:33:58 2011 romain tholimet
// Last update Sun Feb 20 15:51:01 2011 soufien benramdhane
//

#ifndef				__IOPERAND_HH__
#define				__IOPERAND_HH__

#include			<string>

typedef enum
  {
    NONE = 0,
    INT8,
    INT16,
    INT32,
    FLOAT,
    DOUBLE
  }				eOperandType;

class				IOperand
{
public:
  //Destructeur virtual (remontee des differents destructeurs)
  virtual ~IOperand()		{}
  //Conversion en string
  virtual std::string const&	toString() const = 0;
  //Gestion des Operandes avec le type et la precision (ordre de priorite)
  virtual int			getPrecision() const = 0;
  virtual eOperandType		getType() const = 0;
  //Surcharge d'operateurs pour le calcul entre operandes
  virtual IOperand*		operator+(const IOperand&) const = 0;
  virtual IOperand*		operator-(const IOperand&) const = 0;
  virtual IOperand*		operator/(const IOperand&) const = 0;
  virtual IOperand*		operator*(const IOperand&) const = 0;
  virtual IOperand*		operator%(const IOperand&) const = 0;
};

#endif			/*	__IOPERAND_HH__	*/
