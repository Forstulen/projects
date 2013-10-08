#include		<iostream>
#include		"Protocol.hpp"
#include		"ExplosionObject1.hpp"

namespace		GameObject
{
  //************GAMEOBJECTCLIENT************************//

  ExplosionObject1::ExplosionObject1()
  {
    this->name_ = "basicexplosion";
    this->type_ = Asset::EXPLOSION;
    this->speed_ = 1.0f;
    this->pos_.x = 0;
    this->pos_.y = 0;
    this->gtimer_ = 0;
    this->direction_ = true;
    this->filename_ = "ExplosionObject1";
    this->death_ = false;
    this->group_ = Asset::NOCOLLISION;
    this->score_ = 0;
	this->setDirVector(0, 0);

	this->id_ = -1;
    this->parentId_ = -1;
    this->dim_.x = 0;
	this->dim_.y = 0;
    this->currentRect_ = 0;
    this->startIndex_ = 0;
	this->parent_ = NULL;
    this->fireInterval_ = 0.0;
    this->currentEvent_ = Protocol::RT_EVENT_NONE;
  }

  ExplosionObject1::~ExplosionObject1()
  {
  }

  void					ExplosionObject1::initObject(float posX, float posY, float width,
								     float heigth, unsigned int rect, bool dir, const AGameObject * parent)
  {
    this->parent_ = parent;
    this->direction_ = dir;
    this->dim_.x = width;
    this->dim_.y = heigth;
    this->pos_.x = posX;
    this->pos_.y = posY;
    this->currentRect_ = rect;
    this->startIndex_ = rect;
    this->finishedAnim_ = false;
  }

  void						ExplosionObject1::destroyObject()
  {

  }

  bool						ExplosionObject1::update(float timer)
  {
    this->gtimer_ += timer;
    if (this->currentRect_ == this->startIndex_ && this->finishedAnim_)
      this->death_ = true;
    else if (this->gtimer_ > 0.0167f * 3.0f)
      {
		this->gtimer_ = 0;
		this->finishedAnim_ = true;
		return true;
      }
    return false;
  }

  bool						ExplosionObject1::update(const Network::Packet & packet)
  {
    return false;
  }

  bool						ExplosionObject1::update(float, Protocol::eEvent)
  {
    return true;
  }

  bool						ExplosionObject1::isFiring(float timer)
  {
    return false;
  }
}

EXPORT Asset::AGameObject* getGameObject()
{
  return new GameObject::ExplosionObject1;
}
