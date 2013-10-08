#ifndef PARSER_MAP_HPP
#define PARSER_MAP_HPP

#include <vector>
#include "ConsumerParser.hpp"

namespace Parser
{

  class ParserMap : public ConsumerParser
  {
    unsigned int      width_;
    unsigned int      height_;
    unsigned char     **map_;
    public:
    ParserMap();
    ~ParserMap();

    unsigned int  getWidth() const;
    unsigned int  getHeight() const;
    unsigned char **getMap() const;
    bool loadFile(std::string const&);
    bool         parse();
    private:
    bool         fillLine(std::vector<unsigned char>& values,
        unsigned char **toFill);
    bool         isNumber(std::string const&);
    void         fillMap(std::vector<unsigned char*> & map);
  };

}

#endif
