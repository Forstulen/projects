#ifndef		EXCEPT_HPP
#define		EXCEPT_HPP

#include	<ostream>

namespace	Network
{

  /**
   * \class	Except
   */

  struct	Except
  {
    /// methode virtuelle pour afficher l'exception sur un flux.
    ///
    /// affiche sur le flux un message d'erreur à la \c perror, c'est à dire:
    /// nom de la procedure, deux points, espace, message correspondant au code
    /// d'erreur.

    virtual std::ostream& print(std::ostream& out) const = 0;

  };
};

#endif
