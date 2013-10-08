//
// AReception.hh for  in /home/allaux_c//rendu/cpp/plazza-2014-tholim_r/sources
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Tue Apr 12 11:19:58 2011 chanh allaux
// Last update Sat Apr 16 18:56:37 2011 chanh allaux
//

#ifndef				__IRECEPTION_HH_
# define			__IRECEPTION_HH_

#include			<vector>
#include			<string>
#include			"Kitchen.hh"

class				IReception
{
public:
  virtual ~IReception() {}

public:
  virtual void			receiveCommand(std::string const &) = 0;
  virtual std::vector<Kitchen::Kitchen *> const &	getKitchenList(void) = 0;
  virtual void			updateNbPizza(const Kitchen::Kitchen*) = 0;
};

#endif
