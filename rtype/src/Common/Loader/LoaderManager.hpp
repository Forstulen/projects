#ifndef		LOADERMANAGER_HH
#define		LOADERMANAGER_HH

#include	<string>
#include	<map>

#include	"Singleton.hpp"
#include	"AGameObject.hpp"

namespace	Loader
{

  class					DynamicLibraryLoader;

  class					LoaderManager : public Tools::Singleton<LoaderManager>
  {
    friend class Tools::Singleton<LoaderManager>;

    std::map<std::string, DynamicLibraryLoader *>	dlloader_;

    LoaderManager();

  public:
	~LoaderManager();
    bool				loadObjects();
    Asset::AGameObject *		getObject(std::string const &name);

  private:

    bool				loadLibrary(std::string const &path, std::string const &name);

  };

}

#endif
