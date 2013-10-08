#ifndef TABLE_HPP
#define TABLE_HPP

#include <vector>
#include <map>
#include <string>

namespace RTDB
{
class Table
{
  public:
    typedef std::multimap<std::string, std::vector<std::string> > Rows;
    typedef std::pair<Rows::iterator, Rows::iterator> EqRangeIt;

  private:
    Rows rows_;
    std::string name_;

  public:
    Table(std::string const& name);
    ~Table();

    bool addRow(std::vector<std::string> const&);
    EqRangeIt findId(std::string id);
    std::string const& getName() const;
    Rows const& getRows() const;
};
}

#endif
