#include		"MonsterObject5.hpp"

namespace		GameObject
{

  //************GAMEOBJECTCLIENT************************//

  MonsterObject5::MonsterObject5()
  {
    this->name_ = "monster5";
    this->type_ = Asset::MONSTER;
    this->speed_ = 30.0f;
    this->fireInterval_ = 150.0f;
    this->pos_.x = 0;
    this->pos_.y = 0;
    this->gtimer_ = 0;
    this->fireWaitingTimer_ = 0;
    this->direction_ = false;
    this->filename_ = "MonsterObject5";
    this->death_ = false;
    this->group_ = Asset::OTHER;
    this->score_ = 0;
    this->angle_ = 0;
    this->sign_ = 1;
    this->healthPoint_ = 1;
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

  MonsterObject5::~MonsterObject5()
  {
  }

  void						MonsterObject5::initObject(float posX, float posY, float width, 
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
    this->savePosY_ = this->pos_.y;
  }

  void						MonsterObject5::destroyObject()
  {

  }

  bool						MonsterObject5::update(float timer)
  {
    this->pos_.x += !this->direction_ ? -this->speed_ * timer : this->speed_ * timer;
	this->pos_.y += !this->direction_ ? -this->speed_ * timer : this->speed_ * timer;
 
    this->gtimer_ += timer;
    if (this->gtimer_ > 0.0167f * 10.0f)
      {
	this->gtimer_ = 0;
	return true;
      }
    return false;
  }

  bool						MonsterObject5::update(const Network::Packet & packet)
  {
    return true;
  }

  bool						MonsterObject5::update(float, Protocol::eEvent)
  {
    return true;
  }

  bool						MonsterObject5::isFiring(float timer)
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
  return new GameObject::MonsterObject5;
}
