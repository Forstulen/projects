cmake_minimum_required		(VERSION	2.6)

#		Project Name

project				(Server)

#		Common: Including files in common.
#			(See common_macors.cmake to add files from the Common folder)

include				(../Common/common_macros.cmake)

#		Creation of Libraries and output libraries

set				(LIBRARY_OUTPUT_PATH
						../../resource/Libraries)

add_library			(MonsterObject1		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/MonsterObject1.hpp ${COMMON}GameObject/MonsterObject1.cpp)
add_library			(MonsterObject2		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/MonsterObject2.hpp ${COMMON}GameObject/MonsterObject2.cpp)
add_library			(MonsterObject3		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/MonsterObject3.hpp ${COMMON}GameObject/MonsterObject3.cpp)
add_library			(MonsterObject4		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/MonsterObject4.hpp ${COMMON}GameObject/MonsterObject4.cpp)
add_library			(MonsterObject5		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/MonsterObject5.hpp ${COMMON}GameObject/MonsterObject5.cpp)
add_library			(MonsterObject6		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/MonsterObject6.hpp ${COMMON}GameObject/MonsterObject6.cpp)
add_library			(MonsterPowerUpSpeed		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/MonsterPowerUpSpeed.hpp ${COMMON}GameObject/MonsterPowerUpSpeed.cpp)
add_library			(MonsterPowerUpBeam2		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/MonsterPowerUpBeam2.hpp ${COMMON}GameObject/MonsterPowerUpBeam2.cpp)
add_library			(BulletObject1		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/BulletObject1.hpp ${COMMON}GameObject/BulletObject1.cpp)
add_library			(BulletObject2		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/BulletObject2.hpp ${COMMON}GameObject/BulletObject2.cpp)
add_library			(WallObject1		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/WallObject1.hpp ${COMMON}GameObject/WallObject1.cpp)
add_library			(PlayerObject1		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/PlayerObject1.hpp ${COMMON}GameObject/PlayerObject1.cpp)
add_library			(BulletMonsterObject1		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/BulletMonsterObject1.hpp ${COMMON}GameObject/BulletMonsterObject1.cpp)
add_library			(ExplosionObject1	SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/ExplosionObject1.hpp ${COMMON}GameObject/ExplosionObject1.cpp)
add_library			(PowerUpObjectBeam2		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/PowerUpObjectBeam2.hpp ${COMMON}GameObject/PowerUpObjectBeam2.cpp)
add_library			(PowerUpObjectSpeed		SHARED ${ASSETS}AGameObject.cpp ${ASSETS}AGameObject.hpp ${COMMON}GameObject/PowerUpObjectSpeed.hpp ${COMMON}GameObject/PowerUpObjectSpeed.cpp)
