#include	<sstream>
#include	<iostream>
#include	"AssetManager.hpp"
#include	"Exception.hpp"

namespace	Asset
{
  AssetManager::AssetManager():
    db_(RTDB::Database::getInstance())
  {
  }

  AssetManager::~AssetManager()
  {
  }

  void							AssetManager::loadAssets()
  {
    RTDB::Table						*tableFolder = this->db_["Folders"];

    if (!(tableFolder = this->db_["Folders"]))
      throw Exception("AssetManager", "Unable to load Assets");
    RTDB::Table::Rows const& rows = tableFolder->getRows();
		
    for(RTDB::Table::Rows::const_iterator it = rows.begin(); it != rows.end(); it++)
      {
	std::cout << it->second.at(0) << std::endl;
	if (!it->second.at(1).compare("Images"))
	  this->getCollisionInformationsFromFile(it->second.at(0));
      }
  }

  void					AssetManager::getCollisionInformationsFromFile(const std::string & folder)
  {
    RTDB::Table				*tableImage = this->db_["Images"];
  
    if (!tableImage)
      throw Exception("AssetManager", "Unable to load Assets");
    RTDB::Table::Rows const&		rows = tableImage->getRows();
    RTDB::Table::Rows::const_iterator	it = rows.begin();
    for(; it != rows.end(); it++)
      {
	std::string			imagePath(folder + it->second.at(0) + ".xpm");
	Parser::Xpm			parser;


	parser.loadFile(imagePath);
	Asset::AssetInformation<unsigned char **>	collisionInfo;

	std::cout << "\033[45mAssetManager: Loading " << it->second.at(1) << "\033[0m" << std::endl;
	if (!parser.parse())
	{
          continue ;
	}
	this->collisionLibMap_[it->second.at(0)] = parser.getMap();
	if (!this->collisionLibMap_[it->second.at(0)])
	  std::cout << "\033[41mAssetManager: Fail to getMap " << imagePath << "\033[0m" << std::endl;
	collisionInfo.setName(it->second.at(1));
	this->createRect(collisionInfo, it->second);
	this->collisionInformationMap_.insert(std::pair<const std::string, Asset::AssetInformation<unsigned char **> >(it->second.at(1), collisionInfo));
      }
  }

  void					AssetManager::createRect(Asset::AssetInformation<unsigned char **> & collisionInfo, const std::vector<std::string> & data)
  {
    unsigned char			**tmp = this->collisionLibMap_.at(data.at(0));
    const int				startPosX = Conversions::convertString<int>(data.at(2));
    const int				startPosY = Conversions::convertString<int>(data.at(3));
    const int				endPosX = Conversions::convertString<int>(data.at(4));
    const int				endPosY = Conversions::convertString<int>(data.at(5));
    const int				spriteWidth = Conversions::convertString<int>(data.at(6));
    const int				spriteHeight = Conversions::convertString<int>(data.at(7));

    for (int lines = startPosY; lines < endPosY && (lines + spriteHeight) <= endPosY; lines += spriteHeight)
      for (int cols = startPosX; cols < endPosX && (cols + spriteWidth) <= endPosX; cols += spriteWidth)
	{
	  unsigned char				** collisionArray = new unsigned char *[spriteHeight];

	  for (int y = lines, posY = 0; y < lines + spriteHeight; ++y, ++posY)
	    collisionArray[posY] = tmp[y] + cols;
	  
	  collisionInfo.setItems(collisionArray);
	}
    collisionInfo.setHeight(spriteHeight);
    collisionInfo.setWidth(spriteWidth);
    collisionInfo.setStartIndex(Conversions::convertString<int>(data.at(9)));
    collisionInfo.setAnimType(static_cast<Asset::eAnimType>(Conversions::convertString<int>(data.at(8))));
  }

  const Asset::AssetInformation<unsigned char **> &	AssetManager::getAssetCollisionInformation(const std::string & name)
  {
    std::map<const std::string, const Asset::AssetInformation<unsigned char **> >::const_iterator it;

    // std::cout << "AssetManager: " << name << ": Loading..." << std::endl;
    if ((it = this->collisionInformationMap_.find(name)) == this->collisionInformationMap_.end())
      throw Exception("AssetManager", "Unable to load Assets" + name);
    return it->second;
  }
}
