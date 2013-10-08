#ifndef					GAMETASK_HPP
# define				GAMETASK_HPP

# include				"Timer.hpp"
# include				"Functor.hpp"

namespace				ServerGame
{
  class					GameTask
  {
    Functor				function_;
    Timer				timer_;
    float				currentDelay_;

  public:
    GameTask() {}
    ~GameTask() {}
  };
}

#endif					/* ! GAMETASK_HPP */
