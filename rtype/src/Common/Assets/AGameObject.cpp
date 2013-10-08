#include "AGameObject.hpp"

namespace		Asset
{

  AGameObject::~AGameObject(void)
  {
  }

  int						AGameObject::getId() const
  {
    return this->id_;
  }
			
  float						AGameObject::getDirVectorX() const
  {
	  return this->dirVec_.x;
  }

   float					AGameObject::getDirVectorY() const
  {
	  return this->dirVec_.y;
  }

  int						AGameObject::getParentId() const
  {
    return this->parentId_;
  }
		
  void					AGameObject::setGroup(const eGroupObject group)
  {
    this->group_ = group;
  }
		
  void					AGameObject::setId(const int id)
  {
    this->id_ = id;
  }
	
  void					AGameObject::setDirVector(float vecX, float vecY)
  {
	  this->dirVec_.x = vecX;
	  this->dirVec_.y = vecY;
  }

  void					AGameObject::setParentId(const int parentId)
  {
    this->parentId_ = parentId;
  }

  float					AGameObject::getPosX() const
  {
	  return this->pos_.x;
  }
			
  float					AGameObject::getPosY() const
  {
	  return this->pos_.y;
  }

  void					AGameObject::setPosX(float x)
  {
	  this->pos_.x = x;
  }
			
  void					AGameObject::setPosY(float y)
  {
	this->pos_.y = y;
  }
			
  eGroupObject				AGameObject::getGroup() const
  {
    return this->group_;
  }

	ePowerUpType				AGameObject::getPowerType() const
	{
		return this->powerType_;
	}

	void						AGameObject::setPowerType(ePowerUpType value)
	{
		this->powerType_ = value;
	}

  float					AGameObject::getSpeed() const
  {
    return this->speed_;
  }
	
  float					AGameObject::getWidth() const
  {
	  return this->dim_.x;
  }
		
  float					AGameObject::getHeight() const
  {
	  return this->dim_.y;
  }

  int					AGameObject::getHealthPoint() const
  {
    return this->healthPoint_;
  }

  void					AGameObject::setHealthPoint(int value)
  {
    this->healthPoint_ = value;
  }

  eGameObjectType		AGameObject::getGameObjectType() const
  {
     return this->type_;
  }

  void				AGameObject::setGameObjectType(const eGameObjectType gameType)
  {
	  this->type_ = gameType;
  }

  bool				AGameObject::updateStatus(float width, float height)
  {
	float			padding = 200.0f;

    if (this->pos_.x > width + padding || this->pos_.x < 0 - padding || 
		this->pos_.y > height + padding || this->pos_.y < 0 - padding)
	{
		this->death_ = true;
		return true;
	}
    return false;
  }
	
	bool				AGameObject::getDeath() const
	{
		return this->death_;
	}

	void				AGameObject::setDeath(bool status)
	{
		this->death_ = status;
	}

  std::string const&		AGameObject::getFilename() const
  {
    return this->filename_;
  }

  const std::string &		AGameObject::getResourceName() const
  {
    return this->name_;
  }

  void			AGameObject::setResourceName(const std::string & newResource)
  {
    this->name_ = newResource;
  }

  bool			AGameObject::getDirection() const
  {
    return this->direction_;
  }

  unsigned int	AGameObject::getCurrentRect() const { return this->currentRect_;
  }

  unsigned int &	AGameObject::getCurrentRectToSet()
  {
    return this->currentRect_;
  }

  bool &			AGameObject::getDirectionToSet()
  {
    return this->direction_;
  }

  void				AGameObject::setCurrentEvent(Protocol::eEvent e)
  {
    this->currentEvent_ = e;
  }

  void AGameObject::addScore(int add)
  {
    this->score_+= add;
  }

  unsigned int AGameObject::getScore() const
  {
    return this->score_;
  }

  bool		AGameObject::updateHealPoint(int value)
  {
    this->healthPoint_ += value;
    return (this->healthPoint_ > 0);
  }
}
