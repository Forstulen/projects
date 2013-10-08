//
// Option.hh for  in /home/allaux_c//rendu/cpp/nibbler-2014-benram_s
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sun Mar 13 15:11:42 2011 chanh allaux
// Last update Sat Mar 19 17:12:44 2011 chanh allaux
//

#ifndef			__OPTION_HH_
# define		__OPTION_HH_

class			Option
{
  bool			_o;
  bool			_w;
  bool			_m;
  bool			_h;
  bool			_v;

public:
  Option() {}
  Option(int argc, char **argv);

public:
  bool			getO(void) const { return (this->_o); }
  bool			getW(void) const { return (this->_w); }
  bool			getM(void) const { return (this->_m); }
  bool			getH(void) const { return (this->_h); }
  bool			getV(void) const { return (this->_v); }
  void			printDescription(std::string const & description);

private:
  void			usage(void) const;
};

#endif
