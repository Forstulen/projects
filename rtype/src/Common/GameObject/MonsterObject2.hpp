#ifndef			MONSTEROBJECT2
#define			MONSTEROBJECT2

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
  class MonsterObject2 : public Asset::AGameObject
  {
    float					fireWaitingTimer_;
    float					centerX_;
    float					centerY_;
    float					angle_;

  public:
    MonsterObject2();
    virtual ~MonsterObject2();
    static float				firstAngle_;

  public:
    virtual void				initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
    virtual void				destroyObject();

    virtual bool				update(float);
    virtual bool				update(const Network::Packet &);
    virtual	bool				update(float, Protocol::eEvent);
    virtual bool				isFiring(float);
  };

  float					MonsterObject2::firstAngle_ = 0;

}

#endif		//	MONSTEROBJECT2
