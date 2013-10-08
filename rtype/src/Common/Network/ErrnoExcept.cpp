#include		<errno.h>
#include		<cstring>
#include		"ErrnoExcept.hpp"

Network::ErrnoExcept::ErrnoExcept(int const c, std::string const &str)
  : CodeExcept(c, str)
{
}

Network::ErrnoExcept::ErrnoExcept(std::string const& str)
  : CodeExcept(errno, str)
{
}

std::ostream&		Network::ErrnoExcept::print(std::ostream& out) const
{
  return out << "Error [" << this->proc_ << "]:" << strerror(this->code_) << std::endl;
}
