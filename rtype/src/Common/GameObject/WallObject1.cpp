#include		"WallObject1.hpp"

namespace		GameObject
{

  //************GAMEOBJECTCLIENT************************//

  WallObject1::WallObject1()
  {
    this->name_ = "wall1";
    this->type_ = Asset::WALL;
    this->speed_ = 50.0f;
    this->pos_.x = 0;
    this->pos_.y = 0;
    this->gtimer_ = 0;
    this->direction_ = true;
    this->filename_ = "WallObject1";
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

  WallObject1::~WallObject1()
  {
  }

  void						WallObject1::initObject(float posX, float posY, float width, 
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

  void						WallObject1::destroyObject()
  {

  }

  bool						WallObject1::update(float timer)
  {
    this->pos_.x += -this->speed_ * timer;
    return false;
  }

  bool						WallObject1::update(const Network::Packet & packet)
  {
    return false;
  }

  bool						WallObject1::update(float, Protocol::eEvent)
  {
    return false;
  }

  bool						WallObject1::isFiring(float timer)
  {
    return false;
  }
}

//****************************************************//

EXPORT Asset::AGameObject* getGameObject()
{
	return new GameObject::WallObject1;
}
