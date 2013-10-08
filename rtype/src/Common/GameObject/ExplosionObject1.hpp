#ifndef			EXPLOSIONOBJECT1
#define			EXPLOSIONOBJECT1

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
	class ExplosionObject1 : public Asset::AGameObject
	{
		bool						finishedAnim_;

		public:
			ExplosionObject1();
			virtual ~ExplosionObject1();
		public:
			virtual void					initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
			virtual void					destroyObject();

			virtual bool					update(float);
			virtual bool					update(const Network::Packet &);
			virtual bool					update(float, Protocol::eEvent);
			virtual	bool					isFiring(float);
	};
}

#endif	//		EXPLOSIONOBJECT1
