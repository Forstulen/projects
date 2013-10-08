#ifndef CONFIGFILE_HPP
#define CONFIGFILE_HPP

#include <string>
#include <fstream>

namespace App
{
  class ConfigFile
  {
  private:
    static const std::string			hostString;
    static const std::string			portString;
    static const std::string			userNameString;
    std::string										path_;
    std::ifstream									istream_;
    std::ofstream									ostream_;
    std::string										host_;
    std::string										port_;
    std::string										userName_;
  public:
    ConfigFile(std::string const &);
  private:
    ConfigFile();
    ConfigFile(ConfigFile&);
    ConfigFile& operator=(ConfigFile&);
    void	parseFile();
    void	readHost(std::string const &);
    void	readPort(std::string const &);
    void	readUserName(std::string const &);
  public:
    std::string const &	getHost() const;
    std::string const &	getPort() const;
    std::string const &	getUserName() const;
    void								setHost(std::string const &);
    void								setPort(std::string const &);
    void								setUserName(std::string const &);
    void								writeFile();
  };
}

#endif
