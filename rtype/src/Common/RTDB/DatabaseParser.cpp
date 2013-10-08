#include "ConsumerParser.hpp"
#include "DatabaseParser.hpp"

namespace RTDB
{
DatabaseParser::DatabaseParser():
  ConsumerParser()
{
}

DatabaseParser::~DatabaseParser()
{}

bool DatabaseParser::nextTable()
{
  if (!this->readUntil('[') && !this->readChar('[')
      || !this->beginCapture("table")
      || !this->readIdentifier())
      return false;
  this->currentTable_.clear();
  if (!this->endCapture("table", this->currentTable_))
    return false;
  if (!this->readUntil('\n'))
    return false;
  this->readChar('\r');
  this->readChar('\n');
  this->readChar('\r');
  return true;
}

bool DatabaseParser::readField(std::string& field)
{
  while (readChar(' ') || readChar('\t'));
  if (!this->beginCapture("field")
      || !this->readIdentifier()
      || !this->endCapture("field", field))
    return false;
  return true;
}

bool DatabaseParser::nextRow()
{
  int i = 0;
  std::string field;

  this->currentRow_.clear();
  while (this->readField(field))
  {
    this->currentRow_.push_back(field);
    while (readChar(' ') || readChar('\t'));
    if (readChar('\n') || readText("\n\r"))
      break;
    else if (!readChar('&'))
      return false;
    i++;
  }
  while (readChar(' ') || readChar('\t') || readChar('\n') || readChar('\r'));
  return i > 0;
}

std::string const& DatabaseParser::getTableName() const
{
  return this->currentTable_;
}

std::vector<std::string> const& DatabaseParser::getRow() const
{
  return this->currentRow_;
}

}
