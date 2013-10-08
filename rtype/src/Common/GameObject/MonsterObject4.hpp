#ifndef			__MONSTEROBJECT4__
#define			__MONSTEROBJECT4__

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
  class MonsterObject4 : public Asset::AGameObject
  {

    float							fireWaitingTimer_;
    double							angle_;
    float							savePosY_;
    char							sign_;

  public:
    MonsterObject4();
    virtual ~MonsterObject4();
  public:
    virtual void					initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
    virtual void					destroyObject();

    virtual bool					update(float);
    virtual bool					update(const Network::Packet &);
    virtual	bool					update(float, Protocol::eEvent);
    virtual bool					isFiring(float);
  };

}

#endif		//	__MONSTEROBJECT4__
