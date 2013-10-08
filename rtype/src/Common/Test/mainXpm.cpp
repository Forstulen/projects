#if 0
#!/bin/bash
g++ mainXpm.cpp ../Parser/ParserXPM.cpp ../Parser/ConsumerParser.cpp -I ../Parser -I ../Conversions -I ../Network -g -o parserXpm
#endif

#include <iostream>
#include <ctime>
#include "ParserXPM.hpp"

int main(int ac, char **av)
{
  unsigned char **map;
  Parser::Xpm xpm;
  xpm.loadFile(av[1]);
  if (!xpm.parse())
    return 1;
  map = xpm.getMap();
  for (int i = 0 ; i < xpm.getHeight(); i++)
  {
    for (int j = 0 ; j < xpm.getWidth(); j++)
    {
      if (map[i][j] == 0)
        std::cout << " ";
      else
        std::cout << 'x';
    }
    std::cout << std::endl;
  }
  return 0;
}
