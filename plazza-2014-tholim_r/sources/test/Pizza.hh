//
// enum.hh for Plazza in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r/sources
// 
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
// 
// Started on  Thu Apr  7 12:52:22 2011 soufien benramdhane
// Last update Thu Apr  7 22:48:53 2011 romain tholimet
//

#ifndef				__PIZZA_HH__
# define			__PIZZA_HH__

# include			<iostream>

namespace			Pizza
{
  typedef enum			TypePizza
    {
      Regina = 1,
      Margarita = 2,
      Americaine = 4,
      Fantasia = 8
    }				TypePizza;

  typedef enum			TaillePizza
    {
      S = 1,
      M = 2,
      L = 4,
      XL = 8,
      XXL = 16
    }				TaillePizza;

  typedef enum			Ingredient
    {
      Pate = 1,
      Tomate = 2,
      Gruyere = 4,
      Jambon = 8,
      Champignon = 16,
      Steak = 32,
      Aubergine = 64,
      Chevre = 128,
      Amour = 256
    }				Ingredient;

  typedef enum			PackPizza
    {
      PackMargarita = Pizza::Pate + Pizza::Tomate + Pizza::Gruyere,
      PackRegina = Pizza::Pate + Pizza::Tomate + Pizza::Gruyere + Pizza::Jambon + Pizza::Champignon,
      PackAmericaine = Pizza::Pate + Pizza::Tomate + Pizza::Gruyere + Pizza::Steak,
      PackFantasia = Pizza::Pate + Pizza::Tomate + Pizza::Aubergine + Pizza::Chevre + Pizza::Amour
    }				PackPizza;

  typedef enum			TimePizza
    {
      TimeMargarita = 1,
      TimeRegina = 2,
      TimeAmericaine = 2,
      TimeFantasia = 4
    }				TimePizza;

  class				Pizza
  {
    size_t			_ingredient;
    size_t			_timeCooking;
    TaillePizza			_size;
    TypePizza			_type;

  public:
    Pizza(TypePizza type, TaillePizza lenght);
    Pizza(const Pizza&);
    ~Pizza();

  public:
    size_t			getIngredient(void) const;
    size_t			getTimeCooking(void) const;
    TaillePizza			getSize(void) const;
    TypePizza			getType(void) const;
  };
}

#endif		/* ! __PIZZA_HH__ */
