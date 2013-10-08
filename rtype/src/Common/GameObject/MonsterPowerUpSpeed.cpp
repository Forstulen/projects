#include		"MonsterPowerUpSpeed.hpp"

namespace		GameObject
{

  //************GAMEOBJECTCLIENT************************//

  MonsterPowerUpSpeed::MonsterPowerUpSpeed()
  {
    this->name_ = "monsterpowerup";
    this->type_ = Asset::MONSTER;
    this->speed_ = 100.0f;
    this->fireInterval_ = 100.0f;
    this->pos_.x = 0;
    this->pos_.y = 0;
    this->gtimer_ = 0;
    this->direction_ = false;
    this->filename_ = "MonsterPowerUpSpeed";
    this->death_ = false;
    this->group_ = Asset::OTHER;
		this->powerType_ = Asset::SPEED;
    this->score_ = 0;
    this->healthPoint_ = 1;

	this->id_ = -1;
    this->parentId_ = -1;
    this->dim_.x = 0;
	this->dim_.y = 0;
    this->currentRect_ = 0;
    this->startIndex_ = 0;
	this->parent_ = NULL;
    this->currentEvent_ = Protocol::RT_EVENT_NONE;
  }

  MonsterPowerUpSpeed::~MonsterPowerUpSpeed()
  {
  }

  void						MonsterPowerUpSpeed::initObject(float posX, float posY, float width, 
									   float heigth, unsigned int rect, bool dir, const AGameObject * parent)
  {
    this->pos_.x = posX;
    this->pos_.y = posY;
    this->direction_ = dir;
	this->dim_.x = width;
    this->dim_.y = heigth;
    this->currentRect_ = rect;
    this->startIndex_ = rect;
    this->parent_ = parent;
  }

  void						MonsterPowerUpSpeed::destroyObject()
  {

  }

  bool						MonsterPowerUpSpeed::update(float timer)
  {
    this->pos_.x += !this->direction_ ? -this->speed_ * timer : this->speed_ * timer;
    this->gtimer_ += timer;
    if (this->gtimer_ > 0.0167f * 10.0f)
      {
	this->gtimer_ = 0;
	return true;
      }
    return false;
  }

  bool						MonsterPowerUpSpeed::update(const Network::Packet & packet)
  {
    return true;
  }

  bool						MonsterPowerUpSpeed::update(float, Protocol::eEvent)
  {
    return true;
  }

  bool						MonsterPowerUpSpeed::isFiring(float timer)
  {
    return false;
  }
}

EXPORT Asset::AGameObject* getGameObject()
{
  return new GameObject::MonsterPowerUpSpeed;
}
