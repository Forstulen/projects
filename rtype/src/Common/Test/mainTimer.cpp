#if 0
  #!/bin/bash
  g++ mainTimer.cpp ../Tools/Timer.cpp -I ../Tools -o timer_test
#endif

#include <iostream>
#include <ctime>
#include "Timer.hpp"

int main()
{
  Tools::Timer t;
  t.reset();
  for (int i = 0; i < 100000; i++)
    for (jnt j = 0; j < 100000; j++)
    {}
  std::cout << t.getElapsedTime() << std::endl;
  return 0;
}
