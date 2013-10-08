#ifndef				SINGLETON_HPP
# define			SINGLETON_HPP

#include			<iostream>

namespace			Tools
{

  template			<typename T>
  class				Singleton
  {

  protected:

    Singleton() {}
    ~Singleton() {}

  public:

    static T&			getInstance()
    {
      static T			instance_;
      return instance_;
    }
  };

};

#endif
