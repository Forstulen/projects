//
// waiter.hh for plazza in /home/tholim_r//plazza-2014-tholim_r/sources/waiter
//
// Made by romain tholimet
// Login   <tholim_r@epitech.net>
//
// Started on  Thu Apr  7 16:41:22 2011 romain tholimet
// Last update Wed Apr 13 17:24:47 2011 chanh allaux
//

#ifndef					__WAITER_HH__
#define					__WAITER_HH__

#include				<string>
#include				<vector>
#include				<map>
#include				<sstream>

#include				"Pizza.hh"

class					Waiter
{
  static std::map<const std::string, Pizza::TypePizza>		pizzaType;
  static std::map<const std::string, Pizza::TaillePizza>	pizzaSize;

public:
  static std::vector<const Pizza::Pizza*>	*takeCommand(const std::string&);

private:
  static const std::string		rewriteCommand(const std::string&);
  static std::vector<const Pizza::Pizza*>	*checkCommand(const std::string&);
  static size_t				getNumberOfPizza(const std::string&);
  static const Pizza::Pizza*		addPizza(const Pizza::Pizza*);
  static const Pizza::Pizza*		getPizza(const std::string&);
  static Pizza::TypePizza		isValidType(const std::string&);
  static Pizza::TaillePizza		isValidSize(const std::string&);
  static size_t				isValidMult(const std::string&);
  static void				fillVector(void);
};

#endif
