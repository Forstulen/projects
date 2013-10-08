#ifndef			__PLAYEROBJECT__
#define			__PLAYEROBJECT__

#include		<string>
#include		<map>
#include		<cmath>
#include		"AGameObject.hpp"

namespace		GameObject
{
	const float diag = 150 * sqrt(2.f) / 2;

  class PlayerObject1 : public Asset::AGameObject
  {

    std::map<Protocol::eEvent, Asset::Vector2f>	movementMap_;

  public:
    PlayerObject1();
    virtual ~PlayerObject1();
  public:
    virtual void					initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
    virtual void					destroyObject();

    virtual bool					update(float);
    virtual bool					update(const Network::Packet &);
	virtual bool					update(float, Protocol::eEvent);
	virtual bool					isFiring(float);

    bool							delimitateShip(const Asset::Vector2f &, float);
  };
}

#endif		//	__PLAYEROBJECT__
