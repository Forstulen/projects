#ifndef			__WALLOBJECT1__
#define			__WALLOBJECT1__

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
	class WallObject1 : public Asset::AGameObject
	{
		public:
			WallObject1();
			virtual ~WallObject1();
		public:
			virtual void					initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
			virtual void					destroyObject();

			virtual bool					update(float);
			virtual bool					update(const Network::Packet &);
			virtual bool					update(float, Protocol::eEvent);
			virtual bool					isFiring(float);
	};
}

#endif		//	__WALLOBJECT1__
