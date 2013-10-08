#ifndef			BULLETMONSTEROBJECT1
#define			BULLETMONSTEROBJECT1

#include		<string>
#include		"AGameObject.hpp"

namespace		GameObject
{
	class BulletMonsterObject1 : public Asset::AGameObject
	{

		public:
			BulletMonsterObject1();
			virtual ~BulletMonsterObject1();
		public:
			virtual void					initObject(float, float, float, float, unsigned int, bool, const AGameObject *);
			virtual void					destroyObject();

			virtual bool					update(float);
			virtual bool					update(const Network::Packet &);
			virtual bool					update(float, Protocol::eEvent);
			virtual	bool					isFiring(float);
	};
}

#endif	//		BULLETMONSTEROBJECT1
