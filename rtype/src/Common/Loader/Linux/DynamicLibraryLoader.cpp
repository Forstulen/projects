#include		"DynamicLibraryLoader.hpp"

Loader::DynamicLibraryLoader::DynamicLibraryLoader(const std::string& libpath)
  : name_(libpath),
    handle_(dlopen(libpath.c_str(), RTLD_LAZY))
{
  if (!this->handle_)
    throw Exception("DynamicLibraryLoader::dlopen", dlerror());
}

Loader::DynamicLibraryLoader::~DynamicLibraryLoader()
{
  dlclose(this->handle_);
}

std::string	Loader::DynamicLibraryLoader::getName() const
{
  return this->name_;
}
