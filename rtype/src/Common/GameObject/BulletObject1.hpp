#ifndef			BULLETOBJECT1
#define			BULLETOBJECT1

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
  class BulletObject1 : public Asset::AGameObject
  {

    bool			launched_;

  public:
    BulletObject1();
    virtual ~BulletObject1();
  public:
    virtual void					initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
    virtual void					destroyObject();

    virtual bool					update(float);
    virtual bool					update(const Network::Packet &);
    virtual bool					update(float, Protocol::eEvent);
    virtual	bool					isFiring(float);
  };
}

#endif	//		BULLETOBJECT1
