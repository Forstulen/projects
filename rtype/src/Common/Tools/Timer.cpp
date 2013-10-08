#include	<iostream>
#include	"Timer.hpp"

namespace Tools
{
  Timer::Timer()
  {
    this->currentTime_ = clock();
  }

  Timer::~Timer()
  {}

  float Timer::getElapsedTime() const
  {
    float ret = static_cast<float>((((clock() - this->currentTime_)) * 1.0) / CLOCKS_PER_SEC);

    return ret;
  }

  void Timer::reset()
  {
    this->currentTime_ = clock();
  }
}
