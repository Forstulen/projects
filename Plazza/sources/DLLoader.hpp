//
// DLLoader.hh for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Tue Mar  8 16:26:36 2011 chanh allaux
// Last update Sun Apr 17 12:07:00 2011 romain tholimet
//

#ifndef			__DLLOADER_HH_
# define		__DLLOADER_HH_

#include		<string>
#include		<dlfcn.h>
#include		"systemError.hh"

template <typename T>
class			DLLoader
{
  T*			_lib;
  void*			_handle;

public:
  DLLoader(std::string const & str)
    :_lib(NULL)
  {
    T*			(*entry)();

    try
      {
	this->_handle = dlopen(str.c_str(), RTLD_LAZY);
	if (!this->_handle)
	  throw exceptionPlazza::systemError(dlerror());
	entry = reinterpret_cast<T* (*)()>(dlsym(this->_handle, "entry"));
	if (!entry)
	  throw exceptionPlazza::systemError(dlerror());
	this->_lib = entry();
	if (!this->_lib)
	  throw exceptionPlazza::systemError(exceptionPlazza::BADLIB);
      }
    catch (const exceptionPlazza::systemError & e)
      {
	if (this->_handle)
	  dlclose(this->_handle);
	if (this->_lib)
	  delete (this->_lib);
	std::cerr << e.getMessage() << std::endl;
	throw;
      }
  }

  ~DLLoader()
  {
    delete (this->_lib);
    dlclose(this->_handle);
  }

  T*			getLib() const { return (this->_lib); };
};

#endif
