#ifndef CONSUMER_PARSER_HPP
# define CONSUMER_PARSER_HPP

#include <map>
#include <string>

typedef std::map<std::string, std::string> Map;

class ConsumerParser
{
  public:
    ConsumerParser();
    ~ConsumerParser();

    bool          loadFile(std::string const& path);
    inline bool   peekChar(char c);
    inline bool   readChar(char c);
    inline bool   readRange(char begin, char end);
    bool          readText(std::string const& text);
    bool          readEOF();
    bool          readUntil(char c);
    bool          readUntilEOF();
    bool          readInteger();
    bool          readIdentifier();
    inline bool   beginCapture(std::string tag);
    inline bool   endCapture(std::string tag, std::string &out);

  private:
    bool          concateStream();
    inline void   consume(int);
    inline void   erase(int);
    inline void   erase(int, int);

  protected:
    std::string   buffer_;
    Map           tags_;
};

void          ConsumerParser::erase(int ind)
{
  Map::iterator it = tags_.begin();
  for (; it != tags_.end(); it++)
    (*it).second.push_back(this->buffer_[ind]);
  this->buffer_.erase(0, 1);
}

void          ConsumerParser::erase(int ind, int ind2)
{
  Map::iterator it = tags_.begin();
  for (; it != tags_.end(); it++)
    (*it).second.append(this->buffer_.substr(ind, ind2 - ind));
  this->buffer_.erase(ind, ind2);
}

bool   ConsumerParser::peekChar(char c)
{
  if (buffer_.size() == 0)
    return false;
  return this->buffer_[0] == c;
}

bool   ConsumerParser::readChar(char c)
{
  if (buffer_.size() == 0)
    return false;
  if (this->peekChar(c))
    this->erase(0, 1);
  else
    return false;
  return true;
}

bool   ConsumerParser::readRange(char begin, char end)
{
  if (begin > end)
    return false;
  if (buffer_.size() == 0)
    return false;
  if (buffer_[0] >= begin && buffer_[0] <= end)
    this->erase(0, 1);
  else
    return false;
  return true;
}

void  ConsumerParser::consume(int count)
{
  if (count <= (int) this->buffer_.size())
    this->erase(0, count);
  else
    this->erase(0, this->buffer_.size());
}

bool   ConsumerParser::beginCapture(std::string tag)
{
  if (this->tags_.find(tag) == this->tags_.end())
    this->tags_[tag] = std::string();
  else
    this->tags_[tag].clear();
  return true;
}

bool   ConsumerParser::endCapture(std::string tag, std::string &out)
{
  if (this->tags_.find(tag) != this->tags_.end())
  {
    out = this->tags_[tag];
    this->tags_.erase(tag);
    return true;
  }
  return false;
}

#endif /* !CONSUMER_PARSER_HPP */
