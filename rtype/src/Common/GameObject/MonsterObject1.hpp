#ifndef			__MONSTEROBJECT1__
#define			__MONSTEROBJECT1__

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
  class MonsterObject1 : public Asset::AGameObject
  {

    float							fireWaitingTimer_;
    double							angle_;
    float							savePosY_;
    char							sign_;

  public:
    MonsterObject1();
    virtual ~MonsterObject1();
  public:
    virtual void					initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
    virtual void					destroyObject();

    virtual bool					update(float);
    virtual bool					update(const Network::Packet &);
    virtual	bool					update(float, Protocol::eEvent);
    virtual bool					isFiring(float);
  };

}

#endif		//	__MONSTEROBJECT1__
