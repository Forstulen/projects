#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "IDrawableObject.hpp"
#include "IWidget.hpp"
#include "Cursor.hpp"
#include "CoreRTYPE.hpp"

namespace Menu
{
  Cursor::Cursor(std::string const &image)
    : currentWidget_(0),
      nameSprite_(image),
      position_(-50, 0),
      index_(Asset::AssetManager::getInstance().getAssetImageInformation(image).getStartIndex()),
      direction_(true),
			hide_(false)
  {
		this->sprite_.SetPosition(position_);
    this->soundBuffer_.LoadFromFile("../../resource/9233.ogg");
    sound_.SetBuffer(this->soundBuffer_);
    sound_.SetPitch(1.5f);
    sound_.SetVolume(50.f);
    this->sprite_.SetImage(Asset::AssetManager::getInstance().getAssetImageInformation(this->nameSprite_).getImage());
    this->sprite_.SetSubRect(Asset::AssetManager::getInstance().getAssetImageInformation(this->nameSprite_).getNextItems(this->index_, this->direction_));
  }
  Cursor::~Cursor() {}

  void		Cursor::draw(sf::RenderWindow *window)
  {
		if (!this->hide_)
			window->Draw(this->sprite_);
  }

  void		Cursor::update(float time)
  {
    static float timer = 0;
    if (timer > App::SIXTY_FPS * 8)
      {
	this->sprite_.SetImage(Asset::AssetManager::getInstance().getAssetImageInformation(this->nameSprite_).getImage());
	this->sprite_.SetSubRect(Asset::AssetManager::getInstance().getAssetImageInformation(this->nameSprite_).getNextItems(this->index_, this->direction_));
	this->sprite_.SetPosition(position_);
	timer = 0;
      }
    timer += time;
  }

	sf::Vector2f	Cursor::getPosition() const
  {
    return this->position_;
  }

	void		Cursor::setCurrentWidget(IWidget *widget)
	{
		if (this->currentWidget_)
			this->sound_.Play();
		this->currentWidget_ = widget;
			if (widget)
			{
				this->position_.x = widget->getPosition().x - this->sprite_.GetSize().x - 20.f;
				this->position_.y = (widget->getPosition().y + this->currentWidget_->getVerticalCenter()) - (this->sprite_.GetSize().y / 2);
				this->sprite_.SetPosition(position_);
			}
			else
				this->sprite_.SetPosition(sf::Vector2f(-50, 0));
	}

  void		Cursor::setPosition(sf::Vector2f position)
  {
    this->position_ = position;
  }

  IWidget		*Cursor::getCurrentWidget() const
  {
    return this->currentWidget_;
  }

	void		Cursor::setHide(bool value)
	{
		this->hide_ = value;
	}
}
