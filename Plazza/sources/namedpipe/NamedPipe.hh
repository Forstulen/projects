//
// NamedPipe.hh for plazza in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r/sources/namedpipe
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Thu Apr  7 12:14:47 2011 soufien benramdhane
// Last update Fri Apr 15 21:37:00 2011 soufien benramdhane
//

#ifndef			__NAMEDPIPE_HH__
# define		__NAMEDPIPE_HH__

# include		<string>
# include		"Pizza.hh"
# include		"Mutex.hh"
# include		"Kitchen.hh"

class			NamedPipe
{
  std::string		_name;
  int			_fd;
  Mutex			*_mutexRead;
  Mutex			*_mutex;

public:
  NamedPipe(std::string const & name);
  ~NamedPipe();

public:
  void			send(int serial);
  void			send(int serial, Kitchen::u_infoSerial const & info);
  int			receive(void);
  void			receive(Kitchen::u_infoSerial & info);

public:
  std::string const &	getName(void) const;
};

#endif
