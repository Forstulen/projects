#include		"DynamicLibraryLoader.hpp"
#include		"LoaderManager.hpp"
#include		"Database.hpp"
#include		"Table.hpp"

Loader::LoaderManager::LoaderManager()
{
}

Loader::LoaderManager::~LoaderManager()
{
  for (std::map<std::string, DynamicLibraryLoader *>::iterator it = this->dlloader_.begin();
       it !=  this->dlloader_.end(); ++it)
    delete (*it).second;
  this->dlloader_.erase(this->dlloader_.begin(), this->dlloader_.end());
}

bool				Loader::LoaderManager::loadObjects()
{
  RTDB::Table			*folder = RTDB::Database::getInstance()["Folders"];
  RTDB::Table			*table = RTDB::Database::getInstance()["Libraries"];
  bool				res = true;

  if (table && folder)
    {
      RTDB::Table::Rows const		&folderRow = folder->getRows();
      RTDB::Table::Rows const		&rows = table->getRows();
      std::string			path;
      RTDB::Table::Rows::const_iterator it;
    for(it = folderRow.begin(); it != folderRow.end(); it++)
	if (!it->second.at(1).compare("Libraries"))
	    path = it->second[0];
    if (it == folderRow.end())
      std::cout << "LoadManager : No path specified in database. Path is current directory." << std::endl;
    for (it = rows.begin(); it != rows.end(); ++it)
      for (std::vector<std::string>::const_iterator lib = it->second.begin(); lib != it->second.end(); ++lib)
	if (!this->loadLibrary(path, *lib))
	  res = false;
    return res;
    }
  return false;
}

bool			Loader::LoaderManager::loadLibrary(std::string const &path, std::string const &name)
{
  DynamicLibraryLoader *tmp = NULL;

  try
    {
      tmp = new DynamicLibraryLoader(path + "lib" + name + ".so");
      std::cout << "\033[45mLoaderManager: Loading " << path + "lib" + name + ".so" << "\033[0m" << std::endl;
      this->dlloader_[name] = tmp;
    }
  catch (Exception const &e)
    {
      std::cerr << e.where() << ":" << e.what();
      delete tmp;
      return false;
    }
  return true;
}


Asset::AGameObject *	Loader::LoaderManager::getObject(std::string const &name)
{
  return this->dlloader_[name] ? (this->dlloader_[name])->getEntry<Asset::AGameObject *>("getGameObject") : NULL;
}
