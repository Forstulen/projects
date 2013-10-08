#include			<iostream>

#include			"AuthManager.hpp"
#include			"Protocol.hpp"

bool				Connection::AuthManager::bnfLogin(char const c) const
{
  if ((c >= 'a' && c <= 'z') ||
      (c >= 'A' && c <= 'Z') ||
      (c >= '0' && c <= '9') ||
      c == '_')
    return (true);
  return (false);
}

bool				Connection::AuthManager::isValidLogin(std::string const & login, int size) const
{
  std::string::const_iterator	it;
  int				count = 0;

  for (it = login.begin(); it < login.end() && count < size; ++it)
    {
      if (!this->bnfLogin(*it))
	return (false);
      ++count;
    }
  return (true);
}

bool				Connection::AuthManager::scanConnectionPacket(Network::Packet &packet,
									      std::string &login) const
{
  if (packet.getType() == Protocol::RT_TYPE_CONNECTION &&
      packet.getTransactionType() == Protocol::RT_TT_REQUEST &&
      packet.getSubType() == Protocol::RT_SUB_AUTH &&
      this->isValidLogin(packet.getData<char const *>(), packet.getSize()))
    {
      login = std::string(packet.getData<char const *>());
      std::cout << "[AuthManager] New player authentificated : " << login << std::endl;
      packet.setTransactionType(Protocol::RT_TT_ACK);
      packet.setData("", 0);
      return (true);
    }
  packet.setTransactionType(Protocol::RT_TT_ERROR);
  packet.setData("The login you sent is not in the good format.", 46);
  return (false);
}
