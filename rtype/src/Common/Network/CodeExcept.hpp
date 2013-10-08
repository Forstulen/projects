#ifndef		CODE_EXCEPT_HPP
#define		CODE_EXCEPT_HPP

#include	<string>
#include	"Except.hpp"

namespace	Network
{

  /// exception pour les erreurs exprimée par un code \c code.

  class			CodeExcept : public Except
  {

  protected:

    const int		code_;	///< code d'erreur
    const std::string	proc_;	///< nom de la fonction ou s'est produite l'erreur

  public:

    /// \arg \c c le code d'erreur,
    /// \arg \c p le nom de la procedure.

    CodeExcept(int const code, const std::string& proc);

    virtual std::ostream&	print(std::ostream& out) const;
  };

};

std::ostream&	operator << (std::ostream&, Network::CodeExcept const &);

#endif
