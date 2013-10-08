#ifndef		TIMER_HH
# define	TIMER_HH

#include <ctime>

namespace Tools
{
  class		Timer
  {
    clock_t currentTime_;
    public:
    Timer();
    ~Timer();

    float getElapsedTime() const;
    void reset();
  };
}

#endif
