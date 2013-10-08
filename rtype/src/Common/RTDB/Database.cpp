#include "DatabaseParser.hpp"
#include "Database.hpp"
#include "Table.hpp"

namespace RTDB
{

Database::Database()
{
}

Database::~Database()
{
}


bool Database::fillFromFile(std::string const& file)
{
  DatabaseParser dp;
  if (!dp.loadFile(file))
    return false;
  while (dp.nextTable())
  {
    Table *newT = new Table(dp.getTableName());
    while (dp.nextRow())
      newT->addRow(dp.getRow());
    this->tableVector_.push_back(newT);
  }
  return true;
}

Table *Database::operator[](std::string const& name)
{
  std::vector<Table*>::iterator it = this->tableVector_.begin();
  for (; it != this->tableVector_.end() ; it++)
  {
    if ((*it)->getName() == name)
      return *it;
  }
  return 0;
}

}
