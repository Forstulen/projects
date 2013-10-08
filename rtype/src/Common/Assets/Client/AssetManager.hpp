#ifndef			ASSETMANAGER_HPP_
#define			ASSETMANAGER_HPP_

#include		<map>
#include		<string>
#include		<SFML/Graphics.hpp>
#include		<SFML/Audio.hpp>
#include		"ParserXPM.hpp"
#include		"Table.hpp"
#include		"Database.hpp"
#include		"Conversions.hpp"
#include		"AssetSoundInformation.hpp"
#include		"AssetImageInformation.hpp"
#include		"Singleton.hpp"

namespace		Asset
{

  class			AssetManager : public Tools::Singleton<AssetManager>
  {

    friend class	Tools::Singleton<AssetManager>;

    RTDB::Database									&db_;
    Parser::Xpm										parser_;
    std::map<const std::string, sf::Image>						imageLibMap_;
    std::map<const std::string, sf::SoundBuffer>					soundLibMap_;
    std::map<const std::string, unsigned char **>					collisionLibMap_;
    std::map<const std::string, Asset::AssetImageInformation>			imageInformationMap_;
    std::map<const std::string, Asset::AssetSoundInformation>			soundInformationMap_;
    std::map<const std::string, Asset::AssetInformation<unsigned char **> >	collisionInformationMap_;

    AssetManager();
    AssetManager (const AssetManager&);
    AssetManager& operator=(const AssetManager &);

  public:
    ~AssetManager();

  public:
    void						loadAssets();

    void						getImageInformationsFromFile(const std::string &);
    void						createRect(Asset::AssetImageInformation &, const std::vector<std::string> &);

    void						getSoundInformationsFromFile(const std::string &);

    void						getCollisionInformationsFromFile(const std::string &);
    void						createRect(Asset::AssetInformation<unsigned char **> &, const std::vector<std::string> &);

    const Asset::AssetImageInformation 	&		getAssetImageInformation(const std::string &);
    const Asset::AssetSoundInformation	&		getAssetSoundInformation(const std::string &);
    const Asset::AssetInformation<unsigned char **> &	getAssetCollisionInformation(const std::string &);
  };
}

#endif		/*	ASSETMANAGER_CLIENT_HPP_	*/
