#ifndef				SERVERGAME_HPP
# define			SERVERGAME_HPP

# include			<list>
# include			"GameObject.hpp"

namespace			ServerGame
{
  class				ServerGame
  {
    std::list<GameObject *>	objects_;
    Timer			time_;
    int				delay_;
  };
}

#endif				/* SERVERGAME_HPP */
