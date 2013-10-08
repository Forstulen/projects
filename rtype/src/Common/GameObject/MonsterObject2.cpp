#include		<math.h>
#include		<iostream>

#include		"MonsterObject2.hpp"

namespace		GameObject
{

  //************GAMEOBJECTCLIENT************************//

  MonsterObject2::MonsterObject2()
  {
    this->name_ = "monster2";
    this->type_ = Asset::MONSTER;
    this->speed_ = 50.0f;
    this->pos_.x = 0;
    this->fireInterval_ = 200.0f;
    this->pos_.y = 0;
    this->gtimer_ = 0;
    this->fireWaitingTimer_ = 0;
    this->direction_ = false;
    this->filename_ = "MonsterObject2";
    this->death_ = false;
    this->group_ = Asset::OTHER;
    this->score_ = 0;
    this->healthPoint_ = 2;
    this->score_ = 200;
    this->setDirVector(0, 0);

	this->id_ = -1;
    this->parentId_ = -1;
    this->dim_.x = 0;
	this->dim_.y = 0;
    this->currentRect_ = 0;
    this->startIndex_ = 0;
	this->parent_ = NULL;
    this->currentEvent_ = Protocol::RT_EVENT_NONE;
  }

  MonsterObject2::~MonsterObject2()
  {
  }

  void						MonsterObject2::initObject(float posX, float posY, float width, 
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
    this->centerX_ = this->pos_.x;
    this->centerY_ = this->pos_.y;
    this->angle_ = MonsterObject2::firstAngle_;
    MonsterObject2::firstAngle_ += 0.20;
    if (MonsterObject2::firstAngle_ >= 4.8)
      MonsterObject2::firstAngle_ = 0;
  }

  void						MonsterObject2::destroyObject()
  {

  }

  bool						MonsterObject2::update(float timer)
  {
    this->centerX_ += this->direction_ ? this->speed_ * timer : -this->speed_ * timer;
    this->angle_ += this->direction_ ? timer : -timer;
    this->pos_.x = this->centerX_ + 125 * cos(this->angle_);
    this->pos_.y = this->centerY_ + 125 * sin(this->angle_);
    this->gtimer_ += timer;
    if (this->gtimer_ > 0.0167f * 25.0f)
      {
	this->gtimer_ = 0;
	return true;
      }
    return false;
  }

  bool						MonsterObject2::update(const Network::Packet & packet)
  {
    return true;
  }

  bool						MonsterObject2::update(float, Protocol::eEvent)
  {
    return true;
  }

  bool						MonsterObject2::isFiring(float timer)
  {
    this->fireWaitingTimer_ += timer;
    if (this->fireWaitingTimer_ > 0.0167f * this->fireInterval_)
      {
	this->fireWaitingTimer_ = 0;
	return true;
      }
    return false;
  }

}

EXPORT Asset::AGameObject* getGameObject()
{
	return new GameObject::MonsterObject2;
}
