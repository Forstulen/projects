#include		<iostream>
#include		"PlayerObject1.hpp"
#include		"Protocol.hpp"


namespace		App
{
	const float					SIXTY_FPS = 0.016f;
	const float					WIDTH = 800;
	const float					HEIGHT = 480;
}

namespace		GameObject
{

  //************GAMEOBJECTCLIENT************************//

  PlayerObject1::PlayerObject1()
  {
    this->currentEvent_ = Protocol::RT_EVENT_NONE;
    this->name_ = "blueship";
    this->type_ = Asset::PLAYER;
    this->speed_ = 0.05f;
    this->pos_.x = 0;
    this->pos_.y = 0;
    this->gtimer_ = 0;
    this->direction_ = true;
    this->filename_ = "PlayerObject1";
    this->death_ = false;
    this->group_ = Asset::FRIENDS;
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


    Asset::Vector2f		down = {0, 150};
    Asset::Vector2f		up = {0, -150};
    Asset::Vector2f		left = {-150, 0};
    Asset::Vector2f		right = {150, 0};
    Asset::Vector2f		upLeft = {-diag, -diag};
    Asset::Vector2f		upRight = {diag, -diag};
    Asset::Vector2f		downLeft = {-diag, diag};
    Asset::Vector2f		downRight = {diag, diag};
	Asset::Vector2f		none = {0, 0};

    this->movementMap_[Protocol::RT_EVENT_DOWN] = down;
    this->movementMap_[Protocol::RT_EVENT_UP] = up;
    this->movementMap_[Protocol::RT_EVENT_LEFT] = left;
    this->movementMap_[Protocol::RT_EVENT_RIGHT] = right;
    this->movementMap_[Protocol::RT_EVENT_UP_LEFT] = upLeft;
    this->movementMap_[Protocol::RT_EVENT_UP_RIGHT] = upRight;
    this->movementMap_[Protocol::RT_EVENT_DOWN_LEFT] = downLeft;
    this->movementMap_[Protocol::RT_EVENT_DOWN_RIGHT] = downRight;
    this->movementMap_[Protocol::RT_EVENT_NONE] = none;
  }

  PlayerObject1::~PlayerObject1()
  {
  }

  void							PlayerObject1::initObject(float posX, float posY, float width, 
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

  void							PlayerObject1::destroyObject()
  {

  }

  bool							PlayerObject1::update(float timer)
  {
    bool						ret = false;

    this->gtimer_ += timer;
    if (this->gtimer_ > 0.0167f * 5)
      {
	this->gtimer_ = 0;
	if (this->currentEvent_ == Protocol::RT_EVENT_UP || this->currentEvent_ == Protocol::RT_EVENT_UP_LEFT
	    || this->currentEvent_ == Protocol::RT_EVENT_UP_RIGHT)
	  {
	    this->direction_ = true;
	    ret = true;
	  }
	else if (this->currentEvent_ == Protocol::RT_EVENT_DOWN || this->currentEvent_ ==
		 Protocol::RT_EVENT_DOWN_LEFT || this->currentEvent_ == Protocol::RT_EVENT_DOWN_RIGHT)
	  {
	    this->direction_ = false;
	    ret = true;
	  }
	else if ((this->currentEvent_ == Protocol::RT_EVENT_NONE || this->currentEvent_ ==
		  Protocol::RT_EVENT_LEFT || this->currentEvent_ == Protocol::RT_EVENT_RIGHT) && this->currentRect_ != this->startIndex_)
	  {
	    if (this->direction_)
	      --this->currentRect_;
	    else
	      ++this->currentRect_;
	  }
      }
    Asset::Vector2f			move = this->movementMap_[this->currentEvent_];

    if (this->delimitateShip(move, timer))
      {
	this->pos_.x += move.x * timer;
	this->pos_.y += move.y * timer;
      }
    return ret;
  }

  bool							PlayerObject1::update(const Network::Packet & packet)
  {
    const Protocol::PlayerEvent	*dataObject = packet.getData<const Protocol::PlayerEvent*>();

    this->pos_.x = dataObject->x;
    this->pos_.y = dataObject->y;

    return false;
  }

  bool							PlayerObject1::update(float timer, Protocol::eEvent key)
  {
    return false;
  }

  bool						PlayerObject1::delimitateShip(const Asset::Vector2f & move, float time)
  {
    return  ((move.x * time + this->pos_.x) > 0 &&
	     (move.x * time + this->pos_.x) < (App::WIDTH - this->dim_.x) &&
	     (move.y * time + this->pos_.y) < (App::HEIGHT - this->dim_.y - 50) &&
	     (move.y * time + this->pos_.y) > 0);
  }

  bool						PlayerObject1::isFiring(float timer)
  {
    return false;
  }

}

//****************************************************//

EXPORT Asset::AGameObject* getGameObject()
{
	return new GameObject::PlayerObject1;
}

