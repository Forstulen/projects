#ifndef DATABASE_PARSER_HPP
#define DATABASE_PARSER_HPP

#include <vector>
#include <string>
#include "ConsumerParser.hpp"

namespace RTDB
{
class DatabaseParser : public ConsumerParser
{
  std::string currentTable_;
  std::vector<std::string> currentRow_;
  public:
    DatabaseParser();
    ~DatabaseParser();

    bool nextTable();
    bool nextRow();
    bool readField(std::string&);
    std::string const& getTableName() const;
    std::vector<std::string> const& getRow() const;
};
}

#endif
