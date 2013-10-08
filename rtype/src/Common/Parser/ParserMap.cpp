#include "Conversions.hpp"
#include "ParserMap.hpp"

namespace Parser
{

  ParserMap::ParserMap():
    width_(-1), height_(-1), map_(0)
  {}

  ParserMap::~ParserMap()
  {
  }

  unsigned int ParserMap::getWidth() const
  {
    return this->width_;
  }

  unsigned int ParserMap::getHeight() const
  {
    return this->height_;
  }

  unsigned char   **ParserMap::getMap() const
  {
    return this->map_;
  }

  bool ParserMap::loadFile(std::string const& file)
  {
    if (!ConsumerParser::loadFile(file))
      return false;
    return true;
  }

  bool         ParserMap::parse()
  {
    std::string value;
    std::vector<unsigned char*> map;
    std::vector<unsigned char> values;
    bool end = false;

    while (!end)
    {
      this->beginCapture("value");
      if (!this->readInteger())
        return false;
      this->endCapture("value", value);
      values.push_back(static_cast<unsigned char>(Conversions::convertString<unsigned int>(value)));
      if (!this->readChar(';'))
      {
        unsigned char *tab;
        if (!this->readChar('\n'))
        {
          if (!readChar('!') || !fillLine(values, &tab))
            return false;
          end = true;
        }
        else if (!fillLine(values, &tab))
          return false;
        map.push_back(tab);
        values.clear();
      }
    }
    fillMap(map);
    return true;
  }

  bool  ParserMap::isNumber(std::string const& line)
  {
    for (unsigned int i = 0; i < line.size(); i++)
    {
      if (!(line[i] <= '0' && line[i] >= '9'))
        return false;
    }
    return true;
  }

  bool  ParserMap::fillLine(std::vector<unsigned char>& values, unsigned char **toFill)
  {
    if (this->width_ != -1 && values.size() != this->width_)
      return false;
    this->width_ = values.size();
    *toFill = new unsigned char[this->width_];
    for (unsigned int i = 0; i < this->width_ ; i++)
      (*toFill)[i] = values[i];
    return true;
  }

  void  ParserMap::fillMap(std::vector<unsigned char*> & map)
  {
    this->height_ = map.size();
    this->map_ = new unsigned char*[this->height_];
    for (unsigned int i = 0; i < this->height_ ; i++)
      this->map_[i] = map[i];
  }

}
