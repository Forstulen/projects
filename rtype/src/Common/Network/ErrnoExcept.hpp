#ifndef		ERRNO_EXCEPT_HPP
#define		ERRNO_EXCEPT_HPP

#include	"CodeExcept.hpp"

namespace	Network
{

  /// exception pour les erreurs exprimée par un code \c errno.

  struct ErrnoExcept : public CodeExcept
  {
    ErrnoExcept(int const c, std::string const &);
    ErrnoExcept(std::string const&);

    virtual std::ostream&	print(std::ostream& out) const;
  };

};

#endif
