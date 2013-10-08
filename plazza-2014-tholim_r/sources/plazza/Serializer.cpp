//
// Serialiseur.cpp for plazza in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r/sources
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Thu Apr  7 16:38:30 2011 soufien benramdhane
// Last update Sun Apr 17 22:48:25 2011 romain tholimet
//

#include                "Serializer.hh"

int			Serializer::pack(Pizza::Pizza const & pizza)
{
  int			serial = 0;

  serial |= pizza.getType();
  serial <<= 8;
  serial |= pizza.getSize();
  return (serial);
}

Pizza::Pizza		*Serializer::unpack(int serial)
{
  Pizza::TaillePizza	size;
  Pizza::TypePizza	type;

  size = static_cast<Pizza::TaillePizza>(serial & 0x000000FF);
  serial >>= 8;
  type = static_cast<Pizza::TypePizza>(serial & 0x000000FF);
    return (new Pizza::Pizza(type, size));
}
