#ifndef			ANIMATIONMANAGER
#define			ANIMATIONMANAGER

#include		"AssetManager.hpp"
#include		"AssetSoundInformation.hpp"
#include		"AssetImageInformation.hpp"
#include		"EventManager.hpp"
#include		"Singleton.hpp"
#include		"AGameObject.hpp"

namespace		Animation
{

class			AnimationManager : public Tools::Singleton<AnimationManager>
{

	friend class	Tools::Singleton<AnimationManager>;

	Asset::AssetManager	&				resources_;
	sf::Sprite							sprite_;

	AnimationManager();
	AnimationManager (const AnimationManager&);
	AnimationManager& operator=(const AnimationManager &);

public:
	~AnimationManager();

public:
	void		update(float, Asset::AGameObject &);
	void		update(float, Asset::AGameObject &, Protocol::eEvent);
	void		draw(sf::RenderWindow &, const Asset::AGameObject &);
};
}
#endif		/*	ANIMATIONMANAGER	*/
