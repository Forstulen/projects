//
// Pizza.cpp for plazza in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r/sources
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Thu Apr  7 13:04:15 2011 soufien benramdhane
// Last update Wed Apr 13 15:29:30 2011 chanh allaux
//

#include		<map>

#include		"Pizza.hh"

Pizza::Pizza::Pizza(TypePizza type, TaillePizza size)
  : _size(size), _type(type)
{
  std::map<TypePizza, PackPizza> pizza;
  std::map<TypePizza, int> cookingPizza;

  pizza[Regina] = PackRegina;
  pizza[Margarita] = PackMargarita;
  pizza[Americaine] = PackAmericaine;
  pizza[Fantasia] = PackFantasia;
  cookingPizza[Regina] = TimeRegina * 1000000;
  cookingPizza[Margarita] = TimeMargarita * 1000000;
  cookingPizza[Americaine] = TimeAmericaine * 1000000;
  cookingPizza[Fantasia] = TimeFantasia * 1000000;
  this->_ingredient = pizza[type];
  this->_timeCooking = cookingPizza[type];
}

Pizza::Pizza::Pizza(const Pizza& copy)
  : _size(copy.getSize()), _type(copy.getType())
{
  std::map<TypePizza, PackPizza> pizza;
  std::map<TypePizza, int> cookingPizza;

  pizza[Regina] = PackRegina;
  pizza[Margarita] = PackMargarita;
  pizza[Americaine] = PackAmericaine;
  pizza[Fantasia] = PackFantasia;
  cookingPizza[Regina] = TimeRegina * 1000000;
  cookingPizza[Margarita] = TimeMargarita * 1000000;
  cookingPizza[Americaine] = TimeAmericaine * 1000000;
  cookingPizza[Fantasia] = TimeFantasia * 1000000;
  this->_ingredient = pizza[copy.getType()];
  this->_timeCooking = cookingPizza[copy.getType()];
}

Pizza::Pizza::~Pizza()
{
}

/**************************************************/

size_t			Pizza::Pizza::getIngredient(void) const
{
  return (this->_ingredient);
}

size_t			Pizza::Pizza::getTimeCooking(void) const
{
  return (this->_timeCooking);
}

Pizza::TaillePizza	Pizza::Pizza::getSize(void) const
{
  return (this->_size);
}

Pizza::TypePizza	Pizza::Pizza::getType(void) const
{
  return (this->_type);
}
