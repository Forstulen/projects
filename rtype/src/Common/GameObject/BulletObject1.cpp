#include		<iostream>
#include		"Protocol.hpp"
#include		"BulletObject1.hpp"

namespace		GameObject
{
  //************GAMEOBJECTCLIENT************************//

  BulletObject1::BulletObject1()
  {
    this->name_ = "charge";
    this->type_ = Asset::BULLET;
    this->speed_ = 600.0f;
    this->pos_.x = 0;
    this->pos_.y = 0;
    this->gtimer_ = 0;
    this->direction_ = true;
    this->filename_ = "BulletObject1";
    this->launched_ = false;
    this->death_ = false;
    this->group_ = Asset::OTHER;
    this->score_ = 0;
    this->healthPoint_ = 1;
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

  BulletObject1::~BulletObject1()
  {
  }

  void					BulletObject1::initObject(float posX, float posY, float width,
								  float heigth, unsigned int rect, bool dir, const AGameObject * parent)
  {
    this->parent_ = parent;
    if (this->speed_)
      this->direction_ = dir;
	this->dim_.x = width;
    this->dim_.y = heigth;
    this->pos_.x = posX;
    this->pos_.y = posY;
    if (parent)
      {
		this->pos_.x = this->parent_->getPosX() + this->parent_->getWidth();
		this->pos_.y = this->parent_->getPosY() + (this->parent_->getHeight() / 2) - (this->dim_.y / 2);
      }
    this->currentRect_ = rect;
    this->startIndex_ = rect;
  }

  void						BulletObject1::destroyObject()
  {

  }

  bool						BulletObject1::update(float timer)
  {
    if (timer <= 0.0f)
      this->launched_ = true;
    else if (this->parent_ && !this->launched_)
      {
		this->pos_.x = this->parent_->getPosX() + this->parent_->getWidth();
		this->pos_.y = this->parent_->getPosY() + (this->parent_->getHeight() / 2) - (this->dim_.y / 2);
      }
    else
      this->pos_.x += this->direction_ ? this->speed_ * timer : -(this->speed_ * timer);
    this->gtimer_ += timer;
    if (this->gtimer_ > 0.0167f * 3.0f)
      {
		this->gtimer_ = 0;
		return true;
      }
    return false;
  }

  bool						BulletObject1::update(const Network::Packet & packet)
  {
    const Protocol::ModificationBulletData		*dataObject = packet.getData<const Protocol::ModificationBulletData*>();

	if (dataObject)
	{
    this->pos_.x = dataObject->data.posX;
    this->pos_.y = dataObject->data.posY;
    this->direction_ = dataObject->data.direction;

    this->setId(dataObject->data.id);
	}

    return false;
  }

  bool						BulletObject1::update(float, Protocol::eEvent)
  {
    return true;
  }

  bool						BulletObject1::isFiring(float timer)
  {
    return false;
  }
}

EXPORT Asset::AGameObject* getGameObject()
{
  return new GameObject::BulletObject1;
}
