//
// ACore.cpp for  in /home/tholim_r//nibbler-2014-benram_s
// 
// Made by romain tholimet
// Login   <tholim_r@epitech.net>
// 
// Started on  Sat Mar 19 18:42:30 2011 romain tholimet
// Last update Sat Mar 19 18:52:13 2011 romain tholimet
//

#include		<sstream>
#include		"ACore.hh"

void			ACore::openBest(void)
{
  std::fstream		file;
  std::stringstream	ss;

  ss << ".best" << this->getTitle();
  file.open(ss.str().c_str(), std::fstream::out | std::fstream::in);
  if (file.is_open())
    {
      file >> this->_bestScore;
      if (this->_bestScore < 0)
	this->_bestScore = 0;
      file << this->_bestScore;
      file.close();
    }
}

void			ACore::updateBest(void)
{
  std::stringstream	ss;

  ss << ".best" << this->getTitle();
  this->_file.open(ss.str().c_str(), std::fstream::out | std::fstream::in | std::fstream::trunc);
  if (this->_file.is_open())
    {
      if (this->_score > this->_bestScore)
	this->_bestScore = this->_score;
      this->_file << this->_bestScore << std::endl;
      this->_file.close();
    }
}
