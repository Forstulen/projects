
#include		<iostream>
#include		"TCPServer.hpp"

int			main()
{
  Network::TCPServer	*server = NULL;

  try
    {
      Network::TCPServer serv;

      serv.setPort(7000);
      serv.bindSocket();
      server = &serv;
    }
  catch (Network::CodeExcept const &e)
    {
      std::cout << e;
      server = NULL;
    }

  if (server)
    {
      char c;
      std::cout << "OK Press a key" << std::endl;
      std::cin << c;
      delete server;
    }
}


