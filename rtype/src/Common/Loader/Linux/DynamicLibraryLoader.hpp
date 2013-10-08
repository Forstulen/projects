#ifndef		DYNAMICLIBRARYLOADER_HPP
#define		DYNAMICLIBRARYLOADER_HPP

#include	<dlfcn.h>
#include	<iostream>
#include	<string>

#include	"Exception.hpp"

namespace	Loader
{

  class		DynamicLibraryLoader
  {

    std::string	name_;
    void *	handle_;

  public:

    DynamicLibraryLoader(const std::string& libpath);
    ~DynamicLibraryLoader();

    std::string  getName() const;

    template	<typename T>
    T		getEntry(std::string const &entry)
    {
      T		(*func)();

      func = reinterpret_cast<T (*)()>(dlsym(this->handle_, entry.c_str()));
      if (!func)
	throw Exception("DynamicLibraryLoader::getEntry:" + entry, dlerror());
      return func();
    }
  };

}

#endif
