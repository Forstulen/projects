#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <vector>
#include <string>
#include "Singleton.hpp"

namespace RTDB
{

class Table;

class Database : public Tools::Singleton<Database>
{
  friend class Tools::Singleton<Database>;

  std::vector<Table*> tableVector_;
  public:
    ~Database();

    bool fillFromFile(std::string const& file);
    Table *operator[](std::string const& name);
  private:
    Database();
};
}

#endif
