//
// waiter.cpp for plazza in /home/tholim_r//plazza-2014-tholim_r/sources/waiter
//
// Made by romain tholimet
// Login   <tholim_r@epitech.net>
//
// Started on  Thu Apr  7 16:41:17 2011 romain tholimet
// Last update Sun Apr 17 21:01:51 2011 romain tholimet
//

#include			<algorithm>
#include			"Waiter.hh"

std::map<const std::string, Pizza::TypePizza>	Waiter::pizzaType;
std::map<const std::string, Pizza::TaillePizza>	Waiter::pizzaSize;

void				Waiter::fillVector(void)
{
  pizzaType["REGINA"] = Pizza::Regina;
  pizzaType["MARGARITA"] = Pizza::Margarita;
  pizzaType["AMERICAINE"] = Pizza::Americaine;
  pizzaType["FANTASIA"] = Pizza::Fantasia;

  pizzaSize["S"] = Pizza::S;
  pizzaSize["M"] = Pizza::M;
  pizzaSize["L"] = Pizza::L;
  pizzaSize["XL"] = Pizza::XL;
  pizzaSize["XXL"] = Pizza::XXL;
}

std::vector<const Pizza::Pizza*>*	Waiter::takeCommand(const std::string& cmd)
{
  std::string				command(rewriteCommand(cmd));

  transform(command.begin(), command.end(), command.begin(), toupper);
  Waiter::fillVector();
  return (checkCommand(command));
}

std::vector<const Pizza::Pizza*>*	Waiter::checkCommand(const std::string& command)
{
  size_t				start = 0;
  size_t				end;
  size_t				count = 0;
  std::vector<const Pizza::Pizza*>	*pizzaList = new std::vector<const Pizza::Pizza*>;
  const Pizza::Pizza*			pizza;

  while ((end = command.find(';', start)) != std::string::npos)
    {
      pizza = getPizza(command.substr(start, (end - 1) - start));
      count = getNumberOfPizza(command.substr(start, (end - 1) - start));
      while (pizza && count--)
	pizzaList->push_back(addPizza(pizza));
      start = end + 1;
    }
  pizza = getPizza(command.substr(start, std::string::npos));
  count = getNumberOfPizza(command.substr(start, std::string::npos));
  while (pizza && count--)
      pizzaList->push_back(addPizza(pizza));
  return (pizzaList);
}

const Pizza::Pizza*		Waiter::addPizza(const Pizza::Pizza* copy)
{
  return (new Pizza::Pizza(*copy));
}


const std::string		Waiter::rewriteCommand(const std::string& command)
{
  std::string			rewriteCommand(command);
  size_t			ret = -2;

  while ((ret = rewriteCommand.find(";", ret + 2)) != std::string::npos)
    {
      rewriteCommand.insert(ret, " ");
      rewriteCommand.insert(ret + 2, " ");
    }
  return (rewriteCommand);
}

size_t				Waiter::getNumberOfPizza(const std::string& command)
{
  std::stringstream		ss;
  std::string			tmp;
  std::string			mult;
  std::string			end;

  ss << command;
  ss >> tmp >> tmp >> mult >> end;
  if (!end.size())
    return (isValidMult(mult));
  return (0);
}

const Pizza::Pizza*		Waiter::getPizza(const std::string& command)
{
  std::string			type;
  std::string			size;
  std::stringstream		ss;
  Pizza::TypePizza		enumType;
  Pizza::TaillePizza		enumSize;

  ss << command;
  ss >> type >> size;
  enumType = isValidType(type);
  enumSize = isValidSize(size);
  if (enumSize && enumType)
      return (new Pizza::Pizza(enumType, enumSize));
  return (NULL);
}

Pizza::TypePizza		Waiter::isValidType(const std::string& type)
{
  std::map<const std::string, Pizza::TypePizza>::const_iterator	it;

  it = pizzaType.find(type);
  if (it != pizzaType.end())
    return ((*it).second);
  return (static_cast<Pizza::TypePizza>(0));
}

Pizza::TaillePizza		Waiter::isValidSize(const std::string& size)
{
  std::map<const std::string, Pizza::TaillePizza>::const_iterator	it;

  it = pizzaSize.find(size);
  if (it != pizzaSize.end())
    return ((*it).second);
  return (static_cast<Pizza::TaillePizza>(0));
}

size_t				Waiter::isValidMult(const std::string& mult)
{
  std::stringstream		ss;
  size_t			ret;

  if (mult[0] == 'X')
    if (mult.size() > 1)
      {
	for (std::string::const_iterator it = mult.begin() + 1; it != mult.end(); ++it)
	  if (*it < '0' || *it > '9')
	    return (0);
	ss << (mult.c_str() + 1);
	ss >> ret;
	if (ret > 100)
	  {
	    ret = 100;
	    std::cerr << "This pizzeria is not chinese" << std::endl;
	  }
	return (ret);
      }
  return (0);
}
