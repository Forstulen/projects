#ifndef			BULLETOBJECT2
#define			BULLETOBJECT2

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
  class BulletObject2 : public Asset::AGameObject
  {

    bool			launched_;

  public:
    BulletObject2();
    virtual ~BulletObject2();
  public:
    virtual void					initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
    virtual void					destroyObject();

    virtual bool					update(float);
    virtual bool					update(const Network::Packet &);
    virtual bool					update(float, Protocol::eEvent);
    virtual	bool					isFiring(float);
  };
}

#endif	//		BULLETOBJECT2
