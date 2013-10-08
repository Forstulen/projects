#ifndef MAPMANAGER_HPP
#define MAPMANAGER_HPP

#include <map>
#include <vector>
#include <string>
#include "AssetManager.hpp"
#include "Table.hpp"
#include "Database.hpp"
#include "Conversions.hpp"
#include "AGameObject.hpp"

namespace Asset
{
  class MapManager
  {
    public:
      typedef std::map<unsigned int, Asset::AGameObject*> tAliveObjects;
      typedef unsigned char **                   Map;

    private:
      tAliveObjects      *aliveObjects_;
      Map                map_;
      Asset::AGameObject *lastBlock_;
      unsigned int       blockWidth_;
      unsigned int       blockHeight_;
      unsigned int       currentX_;
      unsigned int       widthMap_;
      unsigned int       heightMap_;
      std::string        tableName_;
      RTDB::Database     &db_;

    public:
      MapManager(MapManager::tAliveObjects *objects,
          std::string const& table, unsigned int blockHeight, unsigned int blockWidth);
      ~MapManager();

      bool initFromFile(std::string const& name);
      void setAliveObjects(tAliveObjects *objects);
      void initMap(unsigned int *currentId);
      bool update(unsigned int *currentId);

    private:
      void updateList(unsigned int *currentId);
      void createBlock(std::string const& ressource, int id,
          unsigned int x, unsigned int y);
  };
}

#endif
