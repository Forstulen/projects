#ifndef			__ASSETMANAGER__
#define			__ASSETMANAGER__

#include		<map>
#include		<string>
#include		"ParserXPM.hpp"
#include		"Table.hpp"
#include		"Database.hpp"
#include		"Conversions.hpp"
#include		"AssetInformation.hpp"
#include		"Singleton.hpp"

namespace		Asset
{

  class			AssetManager : public Tools::Singleton<AssetManager>
  {
    friend class	Tools::Singleton<AssetManager>;

    RTDB::Database						db_;
    std::map<const std::string, unsigned char **>		collisionLibMap_;
    std::map<const std::string, const Asset::AssetInformation<unsigned char **> > collisionInformationMap_;

    AssetManager();
    AssetManager (const AssetManager&);
    AssetManager& operator=(const AssetManager &);

  public:
    ~AssetManager();

  public:
    void							loadAssets();
    void							getCollisionInformationsFromFile(const std::string &);
    void							createRect(Asset::AssetInformation<unsigned char **> &, const std::vector<std::string> &);
    const Asset::AssetInformation<unsigned char **> &		getAssetCollisionInformation(const std::string &);
  };
}
#endif		/*	__ASSETMANAGER	*/
