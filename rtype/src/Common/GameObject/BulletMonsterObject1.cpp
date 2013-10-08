#include		<iostream>
#include		"BulletMonsterObject1.hpp"

namespace		GameObject
{
  //************GAMEOBJECTCLIENT************************//

  BulletMonsterObject1::BulletMonsterObject1()
  {
    this->name_ = "bulletmonster";
    this->type_ = Asset::BULLET;
    this->speed_ = 200.0f;
    this->pos_.x = 0;
    this->pos_.y = 0;
    this->gtimer_ = 0;
    this->direction_ = true;
    this->filename_ = "BulletMonsterObject1";
    this->death_ = false;
    this->group_ = Asset::OTHER;
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

  BulletMonsterObject1::~BulletMonsterObject1()
  {
  }

  void					BulletMonsterObject1::initObject(float posX, float posY, float width,
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
  }

  void						BulletMonsterObject1::destroyObject()
  {

  }

  bool						BulletMonsterObject1::update(float timer)
  {
	this->pos_.x += this->dirVec_.x * this->speed_ * timer;
    this->pos_.y += this->dirVec_.y * this->speed_ * timer;

    this->gtimer_ += timer;
    if (this->gtimer_ > 0.0167f * 5.0f)
      {
	this->gtimer_ = 0;
	return true;
      }
    return false;
  }

  bool						BulletMonsterObject1::update(const Network::Packet & packet)
  {
    return false;
  }

  bool						BulletMonsterObject1::update(float, Protocol::eEvent)
  {
    return true;
  }

  bool						BulletMonsterObject1::isFiring(float timer)
  {
    return false;
  }
}

EXPORT Asset::AGameObject* getGameObject()
{
  return new GameObject::BulletMonsterObject1;
}
