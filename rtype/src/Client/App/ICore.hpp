#ifndef ICORE_HPP
#define ICORE_HPP

namespace App
{
  class ICore
  {
  public:
    virtual ~ICore() {}
    virtual bool run() = 0;
  };
}

#endif
