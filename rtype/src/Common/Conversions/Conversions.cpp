#include "Conversions.hpp"

unsigned short		Conversions::encodeToUShort(unsigned char c1, unsigned char c2)
{
  unsigned short	id = 0;
  
  id |= c1;
  id <<= 8;
  id |= c2;
  return (id);
}

void Conversions::fillContentFromShort(Network::Content& content, short header)
{
  content.head.size = header >> 8;
  content.head.type = (header >> 6) & 0x03;
  content.head.tType = (header >> 4) & 0x03;
  content.head.sType = header & 0x0f;
}

void Conversions::fillArray(char *dest, char const* source, unsigned int lenght)
{
	for (unsigned int i = 0; i < lenght; i++)
		dest[i] = source[i];
	dest[lenght] = 0;
}

bool			Conversions::isValidNum(std::string const & num)
{
  std::string::const_iterator it = num.begin();

  for (; it != num.end(); ++it)
    {
      if (*it < '0' && *it > '9')
	return (false);
    }
  return (true); 
}
