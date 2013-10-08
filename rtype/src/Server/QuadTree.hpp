#ifndef				QUADTREE_HPP
# define			QUADTREE_HPP

# include			<list>
# include			<utility>
# include			<map>
# include			<iostream>

# include			"AssetManager.hpp"
# include			"AGameObject.hpp"

template <typename T>
class				QuadTree
{
  QuadTree			*upLeft_;
  QuadTree			*upRight_;
  QuadTree			*downLeft_;
  QuadTree			*downRight_;
  std::list<T *>		obj_;
  unsigned int			depth_;
  float				x_;
  float				y_;
  float				width_;
  float				height_;

  struct			sPoint
  {
    int				x;
    int				y;
  };

  struct			sArea
  {
    sPoint			min;
    sPoint			max;
  };

private:
  QuadTree();
  QuadTree(QuadTree const &);
  QuadTree &			operator=(QuadTree const &);

private:
  bool				isInThisNode(T const & obj) const
  {
    const sPoint		MaxNode[2] = {{this->x_, this->y_}, // cornerUpLeft
					      {this->x_ + this->width_, this->y_ + this->height_}}; // cornerDownRight
    const sPoint		MaxObj[2] = {{obj.getPosX(), obj.getPosY()}, // cornerUpLeft
					     {obj.getPosX() + obj.getWidth(), obj.getPosY() + obj.getHeight()}}; // cornerDownRight

    if (this->checkCorner(MaxNode[1].x, MaxNode[1].y, MaxObj[0].x, MaxObj[0].y) ||
	this->checkCorner(MaxNode[1].x, MaxNode[1].y, MaxObj[0].x, MaxObj[1].y) ||
	this->checkCorner(MaxNode[1].x, MaxNode[1].y, MaxObj[1].x, MaxObj[0].y) ||
	this->checkCorner(MaxNode[1].x, MaxNode[1].y, MaxObj[1].x, MaxObj[1].y) ||
	this->isAllIn(MaxNode, MaxObj))
      return (true);
    return (false);
  }

  bool				addInNode(T *obj, std::list<std::pair<unsigned int, unsigned int> > &listAObject)
  {
    if (!(obj->getDeath()) && !this->obj_.empty() && this->checkPixCollisionWithLists(obj, listAObject))
      {
	obj->setDeath(true);
	this->obj_.push_back(obj);
	return (true);
      }
    this->obj_.push_back(obj);
    return (false);
  }

private:
  bool				checkCorner(float xMax, float yMax,
					    float cornerX, float cornerY) const
  {
    if (this->x_ <= cornerX && this->y_ <= cornerY &&
	xMax >= cornerX && yMax >= cornerY)
      return (true);
    return (false);
  }

  bool				isInSpace(sPoint const &corner, sPoint const corners2[2]) const
  {
    if (corner.x > corners2[0].x && corner.y > corners2[0].y
	&& corner.x < corners2[1].x && corner.y < corners2[1].y)
      return (true);
    return (false);
  }

  bool				isAllIn(sPoint const corners1[2], sPoint const corners2[2]) const
  {
    if (corners1[0].x <= corners2[0].x && corners1[0].y <= corners2[0].y
	&& corners1[1].x >= corners2[1].x && corners1[1].y >= corners2[1].y)
      return (true);
    return (false);
  }

  void				setAreas(sArea &area1, sArea &area2, T const &obj1, T const &obj2, unsigned int count)
  {
    const sPoint		cornersMin1[4] = {{obj2.getPosX() - obj1.getPosX(), 0},
						  {obj2.getPosX() - obj1.getPosX(), obj2.getPosY() - obj1.getPosY()},
						  {0, obj2.getPosY() - obj1.getPosY()},
						  {0, 0}};
    
    const sPoint		cornersMax1[4] = {{obj1.getWidth(), obj2.getPosY() + obj2.getHeight() - obj1.getPosY()},
						  {obj1.getWidth(), obj1.getHeight()},
						  {obj2.getPosX() + obj2.getWidth() - obj1.getPosX(), obj1.getHeight()},
						  {obj2.getPosX() + obj2.getWidth() - obj1.getPosX(), obj2.getPosY() + obj2.getHeight() - obj1.getPosY()}};
    
    const sPoint		cornersMin2[4] = {{0, obj1.getPosY() - obj2.getPosY()},
						  {0, 0},
						  {obj1.getPosX() - obj2.getPosX(), 0},
						  {(obj1.getPosX() - obj2.getPosX()), (obj1.getPosY() - obj2.getPosY())}};

    const sPoint		cornersMax2[4] = {{obj1.getPosX() + obj1.getWidth() - obj2.getPosX(), obj2.getHeight()},
						  {obj1.getPosX() + obj1.getWidth() - obj2.getPosX(), obj1.getPosY() + obj1.getHeight() - obj2.getPosY()},
						  {obj2.getWidth(), obj1.getPosY() + obj1.getHeight() - obj2.getPosY()},
						  {obj2.getWidth(), obj2.getHeight()}};

    area1.min.x = cornersMin1[count].x < 0 ? 0 : cornersMin1[count].x;
    area1.min.y = cornersMin1[count].y < 0 ? 0 : cornersMin1[count].y;
    area1.max.x = cornersMax1[count].x < 0 ? 0 : cornersMax1[count].x;
    area1.max.y = cornersMax1[count].y < 0 ? 0 : cornersMax1[count].y;
    area2.min.x = cornersMin2[count].x < 0 ? 0 : cornersMin2[count].x;
    area2.min.y = cornersMin2[count].y < 0 ? 0 : cornersMin2[count].y;
    area2.max.x = cornersMax2[count].x < 0 ? 0 : cornersMax2[count].x;
    area2.max.y = cornersMax2[count].y < 0 ? 0 : cornersMax2[count].y;
  }

  bool				setAreaToCheck(sArea &area1, sArea &area2, T const &obj1, T const &obj2)
  {
    const sPoint		corners1[4] = {{obj1.getPosX() + obj1.getWidth(), obj1.getPosY()}, // cornerUpRight
					       {obj1.getPosX() + obj1.getWidth(), obj1.getPosY() + obj1.getHeight()}, // cornerDownRight
					       {obj1.getPosX(), obj1.getPosY() + obj1.getHeight()}, // cornerDownLeft
					       {obj1.getPosX(), obj1.getPosY()}}; // cornerUpLeft

    const sPoint		corners2[4] = {{obj2.getPosX() + obj2.getWidth(), obj2.getPosY()}, // cornerUpRight
					       {obj2.getPosX() + obj2.getWidth(), obj2.getPosY() + obj2.getHeight()}, // cornerDownRight
					       {obj2.getPosX(), obj2.getPosY() + obj2.getHeight()}, // cornerDownLeft
					       {obj2.getPosX(), obj2.getPosY()}}; // cornerUpLeft

    const sPoint		extremCorners1[2] = {{obj1.getPosX(), obj1.getPosY()}, // cornerUpLeft
						     {obj1.getPosX() + obj1.getWidth(), obj1.getPosY() + obj1.getHeight()}}; // cornerDownRight

    const sPoint		extremCorners2[2] = {{obj2.getPosX(), obj2.getPosY()}, // cornerUpLeft
						     {obj2.getPosX() + obj2.getWidth(), obj2.getPosY() + obj2.getHeight()}}; // cornerDownRight

    for (unsigned int count = 0; count < 4; ++count)
      {
	if (this->isInSpace(corners1[count], extremCorners2))
	  {
	    this->setAreas(area1, area2, obj1, obj2, count);
	    return (true);
	  }
	if (this->isInSpace(corners2[count], extremCorners1))
	  {
	    this->setAreas(area2, area1, obj2, obj1, count);
	    return (true);
	  }
      }
    return (false);
  }

  bool				checkPixCollision(T &obj1, T &obj2)
  {
    unsigned char **		map1 = Asset::AssetManager::getInstance().getAssetCollisionInformation(obj1.getResourceName()).getItems(obj1.getCurrentRect());
    unsigned char **		map2 = Asset::AssetManager::getInstance().getAssetCollisionInformation(obj2.getResourceName()).getItems(obj2.getCurrentRect());
    sArea			area1;
    sArea			area2;
    int                         maxWidth = obj1.getWidth();
    int                         maxHeight = obj1.getHeight();

    if (this->setAreaToCheck(area1, area2, obj1, obj2) && map1 && map2)
      {
    	for (; area1.min.x < area1.max.x && area1.min.x < maxWidth; area1.min.x += 2, area2.min.x += 2)
    	  for (; area1.min.y < area1.max.y && area1.min.y < maxHeight; area1.min.y += 2, area2.min.y += 2)
    	    {
    	      if (map1[area1.min.y][area1.min.x] == 
    		  map2[area2.min.y][area2.min.x])
    		return (true);
    	    }
      }
    return (false);
  }

  bool				checkPixCollisionWithLists(T *obj, std::list<std::pair<unsigned int, unsigned int> > &listAObject)
  {
    typename std::list<T *>::iterator it = this->obj_.begin();
    bool			ret = false;

    for (; it != this->obj_.end(); ++it)
      if (obj->getGroup() != Asset::NOCOLLISION
	  && obj->getGroup() != (*it)->getGroup()
	  && obj->getGameObjectType() != (*it)->getGameObjectType()
	  && this->checkPixCollision(*obj, *(*it)))
	{
	  ret = true;
	  if (!(*it)->getDeath())
	   {
	     listAObject.push_back(std::pair<unsigned int, unsigned int>(obj->getId(), (*it)->getId()));
	     (*it)->setDeath(true);
	   }
	}
    return (ret);
  }

public:
  QuadTree(unsigned int deep, float x, float y, float width, float height)
    : depth_(deep), x_(x), y_(y), width_(width), height_(height)
  {
    if (!deep)
      {
	this->upLeft_ = NULL;
	this->upRight_ = NULL;
	this->downLeft_ = NULL;
	this->downRight_ = NULL;
      }
    else
      {
	--deep;
	width /= 2;
	height /= 2;
	this->upLeft_ = new QuadTree(deep, x, y, width, height);
	this->upRight_ = new QuadTree(deep, x + width, y, width, height);
	this->downLeft_ = new QuadTree(deep, x, y + height, width, height);
	this->downRight_ = new QuadTree(deep, x + width, y + height, width, height);
      }
  }

  ~QuadTree()
  {
    if (this->depth_)
      {
	delete this->upLeft_;
	delete this->upRight_;
	delete this->downLeft_;
	delete this->downRight_;
      }
  }

public:
  std::list<std::pair<unsigned int, unsigned int> >	*listingOnCollisionObject(std::map<unsigned int, T *> &listAObject)
  {
    typename std::list<std::pair<unsigned int, unsigned int> >	*quad = new std::list<std::pair<unsigned int, unsigned int> >;
    typename std::map<unsigned int, T *>::const_iterator it = listAObject.begin();

    for (; it != listAObject.end(); ++it)
      this->placeAndCheckCollision(it->second, *quad);
    if (!quad->size())
      {
	delete quad;
	quad = NULL;
      }
    this->cleanQuadTree();
    return (quad);
  }

  bool					placeAndCheckCollision(T *obj, std::list<std::pair<unsigned int, unsigned int> > &listAObject)
  {
    if (obj && this->isInThisNode(*obj))
      {
	if (this->depth_)
	  {
	    this->upLeft_->placeAndCheckCollision(obj, listAObject);
	    this->upRight_->placeAndCheckCollision(obj, listAObject);
	    this->downLeft_->placeAndCheckCollision(obj, listAObject);
	    this->downRight_->placeAndCheckCollision(obj, listAObject);
	  }
	else
	    addInNode(obj, listAObject);
	return (true);
      }
    return (false);
  }

public:
  bool					cleanQuadTree()
  {
    if (this->depth_)
      {
	this->upLeft_->cleanQuadTree();
	this->upRight_->cleanQuadTree();
	this->downLeft_->cleanQuadTree();
	this->downRight_->cleanQuadTree();
	return (true);
      }
    this->obj_.clear();
    return (false);
  }

};

#endif				/* QUADTREE_HPP */
