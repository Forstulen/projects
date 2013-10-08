#ifndef			POWERUPOBJECTSPEED_HPP
#define			POWERUPOBJECTSPEED_HPP

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
  class PowerUpObjectSpeed : public Asset::AGameObject
  {
  public:
    PowerUpObjectSpeed();
    virtual ~PowerUpObjectSpeed();
  public:
    virtual void					initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
    virtual void					destroyObject();

    virtual bool					update(float);
    virtual bool					update(const Network::Packet &);
    virtual bool					update(float, Protocol::eEvent);
    virtual bool					isFiring(float);
  };

}

#endif		//	POWERUPOBJECTSPEED_HPP
