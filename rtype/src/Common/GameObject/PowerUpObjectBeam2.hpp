#ifndef			POWERUPOBJECTBEAM2_HPP
#define			POWERUPOBJECTBEAM2_HPP

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
  class PowerUpObjectBeam2 : public Asset::AGameObject
  {
  public:
    PowerUpObjectBeam2();
    virtual ~PowerUpObjectBeam2();
  public:
    virtual void					initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
    virtual void					destroyObject();

    virtual bool					update(float);
    virtual bool					update(const Network::Packet &);
    virtual bool					update(float, Protocol::eEvent);
    virtual bool					isFiring(float);
  };

}

#endif		//	POWERUPOBJECTBEAM2_HPP
