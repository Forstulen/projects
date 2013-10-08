#ifndef				GAMEOBJECTSERVER_HPP
# define			GAMEOBJECTSERVER_HPP

# include			<vector>
# include			"GameTask.hpp"
# include			"CollisionMap.hpp"
# include			"GameTask.hpp"

namespace			ServerGame
{
  class				GameObjectServer : public Assets::AGameObject
  {
    unsigned int		score_;
    CollisionMap		collisionMap_;
    std::vector<GameTask>	tasks_;

  public:
    void			update();
  };
}

#endif				/* ! GAMEOBJECTSERVER_HPP */
