//
// IKitchen.hh for  in /home/allaux_c//rendu/cpp/plazza-2014-tholim_r/sources/plazza
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Wed Apr 13 17:40:05 2011 chanh allaux
// Last update Sun Apr 17 00:23:17 2011 chanh allaux
//

#ifndef					__IKITCHEN_HH_
# define				__IKITCHEN_HH_

#include				<string>
#include				"Pizza.hh"

class					IKitchen
{
public:
  virtual ~IKitchen() {}

public:
  virtual std::string const		&getName() const = 0;
  virtual size_t			getIngredient(Pizza::Ingredient ingredient) const = 0;
  virtual size_t			getCookSleeping() const = 0;
  virtual size_t			getSleeping() const = 0;
  virtual size_t			getTotalCook() const = 0;
};

#endif
