#include <iostream>
#include <exception>
#include "Conversions.hpp"
#include "ConsumerParser.hpp"
#include "ParserXPM.hpp"

namespace Parser {

  Xpm::Xpm()
  {}

  Xpm::~Xpm()
  {}

  bool Xpm::readBlock(std::string const& text)
  {
    if (!(this->readText(text)
          && (this->readChar(' ')
            || this->readChar('\t'))))
      return false;
    while (this->readChar(' ')
        || this->readChar('\t'));
    return true;
  }

  bool Xpm::readHeader()
  {
    if (!this->readText("/* XPM */\n")
        || !this->readBlock("static")
        || !this->readBlock("char")
        || !this->readBlock("*")
        || !this->readUntil('[')
        || !this->readBlock("[]")
        || !this->readBlock("=")
        || !this->readChar('{')
        || !this->readChar('\n'))
      return false;
    return true;
  }

  bool  Xpm::getIntWithTag(std::string const& text, unsigned int &num)
  {
    std::string tmp;

    if (!(this->beginCapture(text)
          && this->readInteger()
          && this->endCapture(text, tmp)))
      return false;
    num = Conversions::convertString<unsigned int>(tmp);
    return true;
  }

  bool  Xpm::getSizes()
  {
    if (!(this->readChar('\"')
          && getIntWithTag("width", this->width_)
          && this->readChar(' ')
          && getIntWithTag("height", this->height_)
          && this->readChar(' ')
          && getIntWithTag("numberColor", this->numberColor_)
          && this->readChar(' ')
          && getIntWithTag("identifierSize", this->identifierSize_)
          && this->readText("\",\n")))
      return false;
    return true;
  }

  bool Xpm::seekBlank(std::string &idColor)
  {
    std::string toCompare;
    unsigned int numberColor = 0;
    bool getIdColor = false;
    while (numberColor < this->numberColor_)
    {
      if (!(this->readChar('\"')
      && (getIdColor || this->beginCapture("idColor"))
      && this->readUntil('\t')
      && (getIdColor || this->endCapture("idColor", idColor))
      && this->readText("\tc ")
      && (getIdColor || this->beginCapture("toCompare"))
      && this->readUntil('\"')
      && (getIdColor || this->endCapture("toCompare", toCompare))
      && this->readText("\",\n")))
          return false;
      if (toCompare.compare("None") == 0)
        getIdColor = true;
      numberColor++;
    }
    return getIdColor;
  }

  bool Xpm::fillLine(int i, std::string const& line)
  {
    for (int j = 0; j < this->width_; j++)
    {
      if (line[j] == this->idColor_[0])
        this->map_[i][j] = 0;
      else
        this->map_[i][j] = 1;
    }
    return true;
  }

  bool  Xpm::parse()
  {
    std::string line;
    if (!this->readHeader()
        || !this->getSizes()
        || !this->seekBlank(this->idColor_))
      return false;
    this->map_ = new unsigned char*[this->height_];
    for (int i = 0; i < this->height_; i++)
    {
      this->map_[i] = new unsigned char[this->width_];
      if (!(this->readChar('\"')
            && this->beginCapture("line")
            && this->readUntil('\"')
            && this->endCapture("line", line)
            && line.size() == this->width_
            && (this->readText("\",\n")
                || this->readText("\"};"))))
        return false;
      fillLine(i, line);
    }
    return true;
  }

  unsigned int Xpm::getWidth() const
  {
    return this->width_;
  }

  unsigned int Xpm::getHeight() const
  {
    return this->height_;
  }

  unsigned char ** Xpm::getMap() const
  {
    return this->map_;
  }
}
