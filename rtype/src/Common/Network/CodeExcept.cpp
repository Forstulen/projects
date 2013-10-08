#include		"CodeExcept.hpp"

Network::CodeExcept::CodeExcept(int const code, const std::string& proc)
  : code_(code), proc_(proc)
{
}

std::ostream&		Network::CodeExcept::print(std::ostream& out) const
{
  return out << "Error #"<< this->code_ <<" [" << this->proc_ << "]" << std::endl;
}

std::ostream&		operator << (std::ostream &out, Network::CodeExcept const &c)
{
  return c.print(out);
}
