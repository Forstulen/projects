#include		<string>
#include		<iostream>

#include		"AuthManager.hpp"
#include		"Packet.hpp"
#include		"Protocol.hpp"

int			 main(int ac, char **av)
{
  std::string		login;
  std::string		loginret;

  if (ac < 2)
    {
      std::cout << "[Test] AuthManager: Enter a login dude!" << std::endl;
      return (0);
    }
  login = av[1];
  std::cout << "[Test] AuthManager at your service: you're name is >>" << login << "<< (" << login.size() << " characters)?" << std::endl;
  Network::Packet		packet(login.c_str(), login.size() + 1,
				       Protocol::RT_TYPE_CONNECTION,
				       Protocol::RT_TT_REQUEST, Protocol::RT_SUB_AUTH);
  Connection::AuthManager	&auth = Connection::AuthManager::getInstance();
  if (auth.scanConnectionPacket(packet, loginret))
    std::cout << "[Test] AuthManager at your service: You're login is right Mr." << loginret << std::endl;
  else
    {
      std::cout << "[Test] AuthManager: It's a bad login dude!" << std::endl;
      if (packet.getTransactionType() == Protocol::RT_TT_ERROR)
	std::cout << "[Test] AuthManager auto message: " << packet.getData<char const *>() << std::endl;
    }
}
