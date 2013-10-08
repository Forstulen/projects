#ifndef			__MONSTEROBJECT5__
#define			__MONSTEROBJECT5__

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
  class MonsterObject5 : public Asset::AGameObject
  {

    float							fireWaitingTimer_;
    double							angle_;
    float							savePosY_;
    char							sign_;

  public:
    MonsterObject5();
    virtual ~MonsterObject5();
  public:
    virtual void					initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
    virtual void					destroyObject();

    virtual bool					update(float);
    virtual bool					update(const Network::Packet &);
    virtual	bool					update(float, Protocol::eEvent);
    virtual bool					isFiring(float);
  };

}

#endif		//	__MONSTEROBJECT5__
