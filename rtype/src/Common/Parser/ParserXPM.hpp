#ifndef PARSER_XPM_HPP
#define PARSER_XPM_HPP

#include <vector>
#include <string>
#include "ConsumerParser.hpp"

namespace Parser
{
  class Xpm : public ConsumerParser
  {
    std::vector<char> colorChar_;
    unsigned int      width_;
    unsigned int      height_;
    unsigned int      numberColor_;
    unsigned int      identifierSize_;
    std::string       idColor_;
    unsigned char     **map_;

    public:
      Xpm();
      ~Xpm();

      bool  parse();
      unsigned char **getMap() const;
      unsigned int getWidth() const;
      unsigned int getHeight() const;
    private:
      Xpm(Xpm const&);
      Xpm& operator=(Xpm const&);

      bool readBlock(std::string const& text);
      bool readHeader();
      bool getSizes();
      bool getIntWithTag(std::string const& text, unsigned int &num);
      bool seekBlank(std::string &idColor);
      bool fillLine(int i, std::string const& line);
  };
}

#endif
