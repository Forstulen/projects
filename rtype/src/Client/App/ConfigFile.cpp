#include <iostream>
#include "ConfigFile.hpp"

namespace App
{
  const std::string ConfigFile::hostString = "host:";
  const std::string ConfigFile::portString = "port:";
  const std::string ConfigFile::userNameString = "username:";

  ConfigFile::ConfigFile(std::string const &path)
    : path_(path), istream_(path.c_str(), std::ios::in)
  {
    if (this->istream_)
      {
	this->parseFile();
      }
    else
      {
	std::cerr << "Error reading config file" << std::endl;
      }
  }

  void	ConfigFile::readHost(std::string const &str)
  {
    if (str.length() <= 15)
      this->host_ = str;
  }

  void	ConfigFile::readPort(std::string const &str)
  {
    if (str.length() <= 5)
      this->port_ = str;
  }

  void	ConfigFile::readUserName(std::string const &str)
  {
    if (str.length() <= 11)
      this->userName_ = str;
  }

  void	ConfigFile::parseFile()
  {
    while (!this->istream_.eof())
      {
	std::string line;
	size_t pos;
	this->istream_ >> line;
	if ((pos = line.find(ConfigFile::hostString)) != std::string::npos)
	  this->readHost(line.substr(pos + ConfigFile::hostString.length()));
	else if ((pos = line.find(ConfigFile::portString)) != std::string::npos)
	  this->readPort(line.substr(pos + ConfigFile::portString.length()));
	else if ((pos = line.find(ConfigFile::userNameString)) != std::string::npos)
	  this->readUserName(line.substr(pos + ConfigFile::userNameString.length()));
      }
    this->istream_.close();
  }

  std::string const &ConfigFile::getHost() const
  {
    return this->host_;
  }

  std::string const &ConfigFile::getPort() const
  {
    return this->port_;
  }

  std::string const &ConfigFile::getUserName() const
  {
    return this->userName_;
  }

  void								ConfigFile::setHost(std::string const &str)
  {
    this->host_ = str;
  }

  void								ConfigFile::setPort(std::string const &str)
  {
    this->port_ = str;
  }

  void								ConfigFile::setUserName(std::string const &str)
  {
    this->userName_ = str;
  }

  void								ConfigFile::writeFile()
  {
    this->ostream_.open(this->path_.c_str(), std::ios::out | std::ios::trunc);
    if (this->ostream_)
      {
	this->ostream_ << ConfigFile::hostString + this->host_;
	this->ostream_ << std::endl;
	this->ostream_ << ConfigFile::portString + this->port_;
	this->ostream_ << std::endl;
	this->ostream_ << ConfigFile::userNameString + this->userName_;
	this->ostream_.close();
      }
    else
      std::cerr << "Error: Could not write config.txt" << std::endl;
  }
}
