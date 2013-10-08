#ifndef			MONSTERPOWERUPSPEED_HPP
#define			MONSTERPOWERUPSPEED_HPP

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
  class MonsterPowerUpSpeed : public Asset::AGameObject
  {
  public:
    MonsterPowerUpSpeed();
    virtual ~MonsterPowerUpSpeed();
  public:
    virtual void					initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
    virtual void					destroyObject();

    virtual bool					update(float);
    virtual bool					update(const Network::Packet &);
    virtual bool					update(float, Protocol::eEvent);
    virtual bool					isFiring(float);
  };

}

#endif
