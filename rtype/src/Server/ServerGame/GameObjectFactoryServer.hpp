#ifndef					GAMEOBJECTFACTORYSERVER_HPP
# define				GAMEOBJECTFACTORYSERVER_HPP

# include				<map>
# include				"AGameObject.hpp"

namespace				ServerGame
{
  class					GameObjectFactoryServer
  {
    std::map<eGameObject, AGameObject*>	objects;

  public:
    AGameObject				*getObject(eGameObject type) const;
  };
}

#endif					/* ! GAMEOBJECTSERVER_HPP */
