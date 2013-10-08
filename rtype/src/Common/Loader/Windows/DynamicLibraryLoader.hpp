#ifndef		DYNAMICLIBRARYLOADER_HPP
#define		DYNAMICLIBRARYLOADER_HPP

#pragma		once
#include	<Windows.h>
#include	<iostream>
#include	<string>

#include	"Exception.hpp"

namespace	Loader
{

  class			DynamicLibraryLoader
  {

    std::string		name_;
    HMODULE		handle_;

  public:

    DynamicLibraryLoader(std::string const &path);
    ~DynamicLibraryLoader();

    std::string		getName() const;

    template		<typename T>
    T			getEntry(const std::string &entry)
    {
      T			(*func)();

      func = reinterpret_cast<T (*)()>(GetProcAddress(this->handle_, reinterpret_cast<LPCTSTR>(entry.c_str())));
      if (!func)
				throw Exception("DynamicLibraryLoader::getEntry", "Failure to find " + entry);
      return func();
    }

  };

}

#endif
