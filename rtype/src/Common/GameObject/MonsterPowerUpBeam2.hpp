#ifndef			MONSTERPOWERUPBEAM2_HPP
#define			MONSTERPOWERUPBEAM2_HPP

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
  class MonsterPowerUpBeam2 : public Asset::AGameObject
  {
  public:
    MonsterPowerUpBeam2();
    virtual ~MonsterPowerUpBeam2();
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
