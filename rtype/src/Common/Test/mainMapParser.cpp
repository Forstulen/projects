#if 0
  #!/bin/bash
  g++ mainMapParser.cpp ../Parser/ParserMap.cpp ../Parser/ConsumerParser.cpp -I ../Parser -I ../Conversions -I ../Network -o parser_test -g
#endif

#include <iostream>
#include <vector>
#include <ctime>
#include "ParserMap.hpp"

int main(int ac, char **av)
{
  ParserMap pm;
  unsigned char      **map;
  if(pm.loadFile(av[1]))
    std::cout << "SUCCESS" << std::endl;
  else
    return 1;
  map = pm.getMap();
  for (int i = 0; i < pm.getHeight(); i++)
  {
    for (int j = 0; j < pm.getWidth(); j++)
      std::cout << map[i][j] << ";";
    std::cout << " " << i << std::endl;
  }
  return 0;
}
