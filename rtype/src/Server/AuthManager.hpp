#ifndef				AUTH_MANAGER_HPP
# define			AUTH_MANAGER_HPP

# include			<string>

# include			"Packet.hpp"
# include			"Singleton.hpp"

namespace			Connection
{
  class				AuthManager
  {
    friend class		Tools::Singleton<AuthManager>;

  public:
    AuthManager() {}
    ~AuthManager() {}
    bool			scanConnectionPacket(Network::Packet &packet,
						     std::string &login) const;
  private:
    bool			isValidLogin(std::string const & login, int size) const;
    bool			bnfLogin(char const c) const;

  private:
    AuthManager(AuthManager const&) {}
    AuthManager& operator=(AuthManager const&) {}
  };
};

#endif				/* ! AUTH_MANAGER_HPP */
