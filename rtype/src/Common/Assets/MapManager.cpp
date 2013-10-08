#include <iostream>
#include "MapManager.hpp"
#include "ParserMap.hpp"
#include "AGameObject.hpp"
#include "LoaderManager.hpp"
#include "Exception.hpp"
#include "Conversions.hpp"

namespace Asset
{
  MapManager::MapManager(MapManager::tAliveObjects *objects,
      std::string const& table, unsigned int blockHeight, unsigned int blockWidth):
    aliveObjects_(objects),
    map_(0),
    lastBlock_(0),
    blockWidth_(blockHeight),
    blockHeight_(blockWidth),
    currentX_(0),
    db_(RTDB::Database::getInstance()),
    tableName_(table)
  {}

  MapManager::~MapManager()
  {}

  bool MapManager::initFromFile(std::string const& name)
  {
    Parser::ParserMap pm;
    if (!pm.loadFile(name) || !pm.parse())
    {
      std::cerr << "MapManager : Unabled to load file [" << name << "]." << std::endl;
      return false;
    }
    this->currentX_ = 0;
    this->map_ = pm.getMap();
    this->widthMap_ = pm.getWidth();
    this->heightMap_ = pm.getHeight();
    return true;
  }

  void MapManager::setAliveObjects(MapManager::tAliveObjects *objects)
  {
    this->aliveObjects_ = objects;
  }
  void MapManager::initMap(unsigned int *currentId)
  {
    int curWidth = 0;
    RTDB::Table *table = this->db_[this->tableName_];
    RTDB::Table::Rows const& rows = table->getRows();
    RTDB::Table::Rows::const_iterator it;
    std::string value;
    if (!table || !rows.size())
      return;
    while (curWidth < (800 + 2 * this->blockWidth_))
    {
      for (int i = 0; i < this->heightMap_; ++i)
      {
        Conversions::toString<unsigned int>(static_cast<unsigned int>(this->map_[i][this->currentX_]), value);
        if (this->map_[i][this->currentX_] && (it = rows.find(value)) != rows.end())
        {
          this->createBlock(it->second[1], *currentId, curWidth, blockHeight_ * i);
          *currentId = *currentId + 1;
        }
      }
      this->currentX_++;
      curWidth += this->blockWidth_;
    }
  }

  bool MapManager::update(unsigned int *currentId)
  {
    if (!this->lastBlock_)
      return false;
    if (this->currentX_ >= this->widthMap_)
      return true;
    if (this->lastBlock_ ->getPosX() + this->blockWidth_ < (800 + 2 * this->blockWidth_))
      this->updateList(currentId);
    return this->currentX_ == this->widthMap_;
  }

  void MapManager::updateList(unsigned int *currentId)
  {
    RTDB::Table *table = this->db_["Map"];
    RTDB::Table::Rows const& rows = table->getRows();
    if (!table || !rows.size())
      return;
    RTDB::Table::Rows::const_iterator it;
    std::string value;
    int x = this->lastBlock_->getPosX();
    for (int i = 0; i < this->heightMap_; ++i)
    {
      Conversions::toString<unsigned int>(static_cast<unsigned int>(this->map_[i][this->currentX_]), value);
      if ((it = rows.find(value)) != rows.end())
      {
        this->createBlock(it->second[1], *currentId, x + blockWidth_, blockHeight_ * i);
        *currentId = *currentId + 1;
      }
    }
    this->currentX_++;
  }

  void MapManager::createBlock(std::string const& resource, int id,
      unsigned int x, unsigned int y)
  {
    Asset::AGameObject *object;
    if (!(object = Loader::LoaderManager::getInstance().getObject("WallObject1")))
      return;
    object->initObject(x, y, this->blockWidth_, this->blockHeight_, 0, true, 0);
    object->setResourceName(resource);
    object->setId(id);
    this->lastBlock_ = object;
    (*this->aliveObjects_)[id] = object;
  }
}
