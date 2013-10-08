//
// Serialiseur.hh for plazza in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r/sources
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Thu Apr  7 16:38:24 2011 soufien benramdhane
// Last update Thu Apr 14 21:58:59 2011 romain tholimet
//

#ifndef			__SERIALIZER_HH__
# define		__SERIALIZER_HH__

# include		"Pizza.hh"

class			Serializer
{
public:
  static int		pack(Pizza::Pizza const & pizza);
  static Pizza::Pizza	*unpack(int serial);
};

#endif			/* ! __SERIALISEUR_HH__ */
