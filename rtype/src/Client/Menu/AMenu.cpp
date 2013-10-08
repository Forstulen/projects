#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <algorithm>
#include "AState.hpp"
#include "IWidget.hpp"
#include "Cursor.hpp"
#include "AMenu.hpp"
#include "StarFieldManager.hpp"
#include "AssetManager.hpp"
#include "ScopedLock.hpp"

namespace Menu
{
	AMenu::AMenu(std::string const &image)
	  : cursor_("cursor"), cursorToUpdate_(false)
	{
		this->sprite_.SetImage(Asset::AssetManager::getInstance().getAssetImageInformation(image).getImage());
		this->soundOk_.SetBuffer(Asset::AssetManager::getInstance().getAssetSoundInformation("sas_ouverture").getSound());
		this->soundOk_.SetVolume(30.f);
		this->sprite_.SetPosition(sf::Vector2f(0, 0));
	}

	void	AMenu::addWidget(IWidget *widget)
	{
		this->widgetList_.push_back(widget);
	}

	void	AMenu::removeWidget(IWidget *widget)
	{
		this->widgetList_.remove(widget);
	}

  void	AMenu::setCursorToUpdate(bool value)
  {
    this->cursorToUpdate_ = value;
  }
	
	void    AMenu::update(float time)
	{
		App::StarFieldManager::getInstance().update(time);
		this->cursor_.update(time);
	}

	void	AMenu::draw(sf::RenderWindow *window)
	{
		App::StarFieldManager::getInstance().draw(window);
		window->Draw(this->sprite_);
		std::list<IWidget*>::iterator	it;
		Thread::ScopedLock<Thread::Mutex> scopedLock(this->mutex_);
		for (it = this->widgetList_.begin(); it != this->widgetList_.end(); ++it)
		{
			if (!(*it)->isHide())
				(*it)->draw(window);
		}
		if (this->cursorToUpdate_)
		  {
		    this->cursorToUpdate_ = false;
		    this->cursor_.setCurrentWidget(this->cursor_.getCurrentWidget());
		  }
		this->cursor_.draw(window);
	}
}
