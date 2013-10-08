#include <istream>
#include <fstream>
#include <string>
#include <cstring>
#include <exception>
#include "ConsumerParser.hpp"

ConsumerParser::ConsumerParser()
{
}

ConsumerParser::~ConsumerParser()
{}

bool ConsumerParser::loadFile(std::string const& path)
{
  unsigned int length;
  std::ifstream ifs(path.c_str());

  if (ifs.is_open())
  {
    ifs.seekg (0, std::ios::end);
    if ((length = static_cast<unsigned int>(ifs.tellg())) == 0)
      return false;
    ifs.seekg (0, std::ios::beg);
    this->buffer_.reserve(length);
    while (!ifs.eof())
      this->buffer_.push_back(ifs.get());
    ifs.close();
    return true;
  }
  else
    return false;
}

bool ConsumerParser::readText(std::string const& text)
{
  if (this->buffer_.size() < text.size())
      return false;
  if (this->buffer_.find(text) == 0)
  {
    consume(text.size());
    return true;
  }
  return false;
}

bool          ConsumerParser::readEOF()
{
  if (!buffer_.empty())
    return false;
  if (buffer_.size() == 0)
    return true;
  return false;
}

bool          ConsumerParser::readUntil(char c)
{
  int         ind;
  if (this->buffer_.empty())
    return false;
  if ((ind = this->buffer_.find(c)) == 0)
    return false;
  consume(ind);
  return true;
}

bool          ConsumerParser::readUntilEOF()
{
  if (!buffer_.empty())
    return false;
  buffer_.clear();
  return true;
}

bool          ConsumerParser::readInteger()
{
  if (buffer_.empty())
    return false;
  if (!readRange('0', '9'))
    return false;
  while (readRange('0', '9'));
  return true;
}

bool          ConsumerParser::readIdentifier()
{
  if (buffer_.empty())
    return false;
  if (!readRange('a', 'z')
      && !readRange('A', 'Z')
      && !readChar('_')
      && !readRange('0', '9')
      && !readChar('.')
	  && !readChar(':')
	  && !readChar('/')
	  && !readChar('\\')
      && !readChar('-'))
    return false;
  while (
      readRange('a', 'z')
      || readRange('A', 'Z')
      || readChar('_')
      || readRange('0', '9')
      || readChar('.')
	  || readChar(':')
	  || readChar('/')
	  || readChar('\\')
      || readChar('-'));
  return true;
}
