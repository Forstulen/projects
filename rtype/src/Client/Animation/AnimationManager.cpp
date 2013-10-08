#include "AnimationManager.hpp"
#include "Protocol.hpp"

namespace	Animation
{
	AnimationManager::AnimationManager(void)
		:resources_(Asset::AssetManager::getInstance())
	{
	}


	AnimationManager::~AnimationManager(void)
	{
	}

	void		AnimationManager::update(float timer, Asset::AGameObject & obj)
	{
		if (obj.update(timer) && !obj.getResourceName().empty())
			Asset::AssetManager::getInstance().getAssetImageInformation(obj.getResourceName()).getNextItems(obj.getCurrentRectToSet(), obj.getDirectionToSet());
	}

	void		AnimationManager::update(float timer, Asset::AGameObject & obj, Protocol::eEvent key)
	{
		obj.setCurrentEvent(key);
		if (obj.update(timer) && !obj.getResourceName().empty())
			Asset::AssetManager::getInstance().getAssetImageInformation(obj.getResourceName()).getNextItems(obj.getCurrentRectToSet(), obj.getDirectionToSet());
	}

	void		AnimationManager::draw(sf::RenderWindow & window, const Asset::AGameObject & obj)
	{
		if (!obj.getResourceName().empty())
		{
			this->sprite_.SetImage(Asset::AssetManager::getInstance().getAssetImageInformation(obj.getResourceName()).getImage());
			this->sprite_.SetSubRect(Asset::AssetManager::getInstance().getAssetImageInformation(obj.getResourceName()).getItems(obj.getCurrentRect()));
			this->sprite_.SetPosition(obj.getPosX(), obj.getPosY());
		}
		window.Draw(this->sprite_);
	}
}
