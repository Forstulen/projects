#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include <sstream>
#include "Packet.hpp"
#include "Conversions.hpp"

namespace Conversions
{

  template		<typename T>
  T			convertString(std::string const& txt)
  {
    T			ret;
    std::stringstream ss(txt);

    ss >> ret;
    return (ret);
  }

  template <typename T>
  void			toString(T const value, std::string &str)
  {
    std::stringstream	ss;

    ss << value;
    ss >> str;
  }

  unsigned short	encodeToUShort(unsigned char c1, unsigned char c2);
  void			fillContentFromShort(Network::Content& content, short header);
  void			fillArray(char *dest, char const*source, unsigned int lenght);
  bool			isValidNum(std::string const & num);
}

#endif
