#include		<iostream>
#include		"Pizza.hh"

int		main()
{
  Pizza::Pizza	pizza(Pizza::Margarita, Pizza::XL, 1);

  std::cout << "Ingredient : " << pizza.getIngredient() << std::endl;
  std::cout << "Time : " << pizza.getTimeCooking() << std::endl;
  std::cout << "Length : " << pizza.getLength() << std::endl;
  std::cout << "Type : " << pizza.getType() << std::endl;
  return (0);
}
