#include	<sstream>
#include	<iostream>
#include	"AssetManager.hpp"
#include	"Database.hpp"
#include	"Exception.hpp"

namespace	Asset
{
  AssetManager::AssetManager()
    :db_(RTDB::Database::getInstance()),
     parser_()
  {
  }


  AssetManager::~AssetManager()
  {
  }

  void						AssetManager::loadAssets()
  {
    RTDB::Table					*tableFolder;

    if (!(tableFolder = this->db_["Folders"]))
      throw Exception("AssetManager", "Unable to load Assets");
    RTDB::Table::Rows const& rows = tableFolder->getRows();	

    for(RTDB::Table::Rows::const_iterator it = rows.begin(); it != rows.end(); ++it)
      {
	if (!it->second.at(1).compare("Images"))
	  {
	    this->getImageInformationsFromFile(it->second.at(0));
	    this->getCollisionInformationsFromFile(it->second.at(0));
	  }
	else if (!it->second.at(1).compare("Sounds"))
	  this->getSoundInformationsFromFile(it->second.at(0));
      }
  }

  void						AssetManager::getImageInformationsFromFile(const std::string & folder)
  {
    RTDB::Table					*tableImage;

    if (!(tableImage = this->db_["Images"]))
      throw Exception("AssetManager", "Unable to load Assets");
    RTDB::Table::Rows const& rows = tableImage->getRows();
    
    for(RTDB::Table::Rows::const_iterator it = rows.begin(); it != rows.end(); it++)
      {
	std::string				imagePath(folder + it->second.at(0) + ".png");

	if (this->imageLibMap_.find(it->second.at(0)) == this->imageLibMap_.end())
	  if (this->imageLibMap_[it->second.at(0)].LoadFromFile(imagePath))
		this->imageLibMap_[it->second.at(0)].SetSmooth(false);
		//throw Exception("AssetManager", "Unable to load Assets");
	if (this->imageInformationMap_.find(it->second.at(1)) == this->imageInformationMap_.end())
	{
	  	Asset::AssetImageInformation		imageInfo;
	
		imageInfo.setName(it->second.at(1));
		imageInfo.setImage(&(this->imageLibMap_[it->second.at(0)]));
		this->createRect(imageInfo, it->second);
		this->imageInformationMap_.insert(std::pair<const std::string, const Asset::AssetImageInformation>(it->second.at(1), imageInfo));
	}
	else
		this->createRect(this->imageInformationMap_.find(it->second.at(1))->second, it->second);
	}
  }

  void						AssetManager::createRect(Asset::AssetImageInformation & imageInfo, const std::vector<std::string> & data)
  {
    const int					startPosX = Conversions::convertString<int>(data.at(2));
    const int					startPosY = Conversions::convertString<int>(data.at(3));
    const int					endPosX = Conversions::convertString<int>(data.at(4));
    const int					endPosY = Conversions::convertString<int>(data.at(5));
    const int					spriteWidth = Conversions::convertString<int>(data.at(6));
    const int					spriteHeight = Conversions::convertString<int>(data.at(7));

    for (int lines = startPosY; lines < endPosY && (lines + spriteHeight) <= endPosY; lines += spriteHeight)
      {
	for (int cols = startPosX; cols < endPosX && (cols + spriteWidth) <= endPosX; cols += spriteWidth)
	  {
	    sf::Rect<int>			rect(cols, lines, cols + spriteWidth, lines + spriteHeight);
	    imageInfo.setItems(rect);
	  }
      }
    imageInfo.setHeight(spriteHeight);
    imageInfo.setWidth(spriteWidth);
    imageInfo.setStartIndex(Conversions::convertString<int>(data.at(9)));
    imageInfo.setAnimType(static_cast<Asset::eAnimType>(Conversions::convertString<int>(data.at(8))));
  }

  void						AssetManager::getSoundInformationsFromFile(const std::string & folder)
  {
    RTDB::Table					*tableSounds = this->db_["Sounds"];

    if (!tableSounds)
      throw Exception("AssetManager", "Unable to load Assets");
    RTDB::Table::Rows const&			rows = tableSounds->getRows();

    for(RTDB::Table::Rows::const_iterator it = rows.begin(); it != rows.end(); it++)
      {
	std::string				soundPath(folder + it->second.at(0) + ".ogg");

	if ((this->soundLibMap_.find(it->second.at(0)) == this->soundLibMap_.end())
	    && !(this->soundLibMap_[it->second.at(0)].LoadFromFile(soundPath)))
	    {
	      std::cerr << "AssetManager: " << soundPath << ": No such file" << std::endl;
	      continue ;
	    }
	
		Asset::AssetSoundInformation		soundInfo;
		soundInfo.setName(it->second.at(0));
		soundInfo.setSound(&(this->soundLibMap_[it->second.at(0)]));
		soundInfo.setLoop(Conversions::convertString<bool>(it->second.at(1)));
		this->soundInformationMap_.insert(std::pair<const std::string, const Asset::AssetSoundInformation>(it->second.at(0), soundInfo));
      }
  }

  void					AssetManager::getCollisionInformationsFromFile(const std::string & folder)
  {
    RTDB::Table				*tableCollision = this->db_["Images"];

    if (!tableCollision)
      throw Exception("AssetManager", "Unable to load Assets");
    RTDB::Table::Rows const&		rows = tableCollision->getRows();
      
    for(RTDB::Table::Rows::const_iterator it = rows.begin(); it != rows.end(); it++)
      {
	std::string			imagePath(folder + it->second.at(0) + ".xpm");

	if (this->collisionLibMap_.find(it->second.at(0)) != this->collisionLibMap_.end())
	  if (this->parser_.loadFile(imagePath))
	    {
	      Asset::AssetInformation<unsigned char**>	collisionInfo;

	      this->collisionLibMap_[it->second.at(0)] = this->parser_.getMap();
	      collisionInfo.setName(it->second.at(1));
	      this->createRect(collisionInfo, it->second);
	      this->collisionInformationMap_.insert(std::pair<const std::string, const
						    Asset::AssetInformation<unsigned char**> >(it->second.at(3), collisionInfo));
	    }
	//  else
	//	throw Exception("AssetManager", "Unable to load Assets");
      }
  }

  void					AssetManager::createRect(Asset::AssetInformation<unsigned char**> & collisionInfo,
								 const std::vector<std::string> & data)
  {
    unsigned char			**tmp = this->collisionLibMap_.at(data.at(0));
    const int				startPosX = Conversions::convertString<int>(data.at(2));
    const int				startPosY = Conversions::convertString<int>(data.at(3));
    const int				endPosX = Conversions::convertString<int>(data.at(4));
    const int				endPosY = Conversions::convertString<int>(data.at(5));
    const int				spriteWidth = Conversions::convertString<int>(data.at(6));
    const int				spriteHeight = Conversions::convertString<int>(data.at(7));

    for (int lines = startPosY; lines >= endPosY; lines += spriteHeight)
      for (int cols = startPosX; cols >= endPosX; cols += spriteWidth)
	{
	  unsigned char			** collisionArray = new unsigned char *[spriteHeight];
	  for (int y = lines, posY = 0; y < lines + spriteHeight; ++y, ++posY)
	    collisionArray[posY] = tmp[y] + cols;
	  collisionInfo.setItems(collisionArray);
	}
    collisionInfo.setHeight(spriteHeight);
    collisionInfo.setWidth(spriteWidth);
    collisionInfo.setStartIndex(Conversions::convertString<int>(data.at(9)));
    collisionInfo.setAnimType(static_cast<Asset::eAnimType>(Conversions::convertString<int>(data.at(8))));
  }

  const Asset::AssetImageInformation &		AssetManager::getAssetImageInformation(const std::string & name)
  {
    if (this->imageInformationMap_.find(name) == this->imageInformationMap_.end())
      throw Exception("AssetManager", "Unable to load Assets" + name);
    return this->imageInformationMap_[name];
  }

  const Asset::AssetSoundInformation &		AssetManager::getAssetSoundInformation(const std::string & name)
  {
    if (this->soundInformationMap_.find(name) == this->soundInformationMap_.end())
      throw Exception("AssetManager", "Unable to load Assets" + name);
    return this->soundInformationMap_[name];
  }

  const Asset::AssetInformation<unsigned char**> &	AssetManager::getAssetCollisionInformation(const std::string & name)
  {
    if (this->collisionInformationMap_.find(name) == this->collisionInformationMap_.end())
      throw Exception("AssetManager", "Unable to load Assets" + name);
    return this->collisionInformationMap_[name];
  }
}
