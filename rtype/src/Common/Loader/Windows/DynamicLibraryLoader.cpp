#include		<string>
#include		"DynamicLibraryLoader.hpp"

Loader::DynamicLibraryLoader::DynamicLibraryLoader(std::string const &libpath)
  : name_(libpath)
{
  this->handle_ = LoadLibrary(reinterpret_cast<LPCTSTR>(libpath.c_str()));
  if (!this->handle_)
    throw Exception("DynamicLibraryLoader", "LoadLibrary " + libpath);
  std::cout << libpath << " loading..." << std::endl; 
}

Loader::DynamicLibraryLoader::~DynamicLibraryLoader()
{
  FreeLibrary(this->handle_);
}

std::string  Loader::DynamicLibraryLoader::getName() const
{
  return this->name_;
}

