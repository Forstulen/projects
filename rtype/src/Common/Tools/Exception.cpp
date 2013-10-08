#include		"Exception.hpp"


std::ostream&	operator << (std::ostream& os, Exception const &e)
{
  return os << "Error in " << e.where() << ":"<< e.what()<< std::endl;
}
