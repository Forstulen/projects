#include "Table.hpp"

namespace RTDB
{
Table::Table(std::string const& name):
  name_(name)
{
}

Table::~Table()
{
}

bool Table::addRow(std::vector<std::string> const& values)
{
  if (values.size() < 1)
    return false;
  this->rows_.insert(std::pair<std::string, std::vector<std::string> >(values[0], values));
  return true;
}

Table::EqRangeIt Table::findId(std::string id)
{
  return (this->rows_.equal_range(id));
}

std::string const& Table::getName() const
{
  return this->name_;
}

Table::Rows const& Table::getRows() const
{
  return this->rows_;
}
}
