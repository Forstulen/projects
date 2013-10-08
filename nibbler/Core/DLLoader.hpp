//
// DLLoader.hh for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Tue Mar  8 16:26:36 2011 chanh allaux
// Last update Thu Mar 10 01:10:32 2011 chanh allaux
//

#ifndef			__DLLOADER_HH_
# define		__DLLOADER_HH_

#include		<string>
#include		"NibblerException.hpp"

template <typename T>
class			DLLoader
{
  T*			_lib;
  void*			_handle;

public:
  DLLoader(std::string const & str)
  {
    T*			(*entry)();

    this->_handle = dlopen(str.c_str(), RTLD_LAZY);
    if (!this->_handle)
      throw nibblerException(dlerror());
    entry = (T* (*)())dlsym(this->_handle, "entry");
    if (!entry)
      throw nibblerException(dlerror());
    this->_lib =  entry();
  }

  ~DLLoader()
  {
    delete (this->_lib);
    dlclose(this->_handle);
  }

  T*			getLib() const { return (this->_lib); };
};

#endif
