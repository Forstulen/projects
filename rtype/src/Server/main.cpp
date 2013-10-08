#include		<iostream>
#include		<string>
#include		<cstdlib>

#include		"Core.hpp"
#include		"Database.hpp"
#include		"LoaderManager.hpp"
#include		"Conversions.hpp"

int			main(int ac, char **av)
{
  std::string		port = "4242";

  if (!RTDB::Database::getInstance().fillFromFile("../../resource/bdd.rtdb"))
  {
    std::cout << "Error : Cannot load database !" << std::endl;
    return 1;
  }
  if (ac > 1)
  {
    port = av[1];
    if (!Conversions::isValidNum(port))
    {
      std::cerr << "Server: Invalid port." << std::endl;
      return EXIT_FAILURE;
    }
  }
  try
  {
    Loader::LoaderManager::getInstance().loadObjects();
    Asset::AssetManager::getInstance().loadAssets();
  }
  catch (...)
  {
    std::cout << "Error on resources initialisation !" << std::endl;
  }
  if (Core::getInstance().set(port.c_str()))
    std::cout << "Server initialized !" << std::endl;
  try
  {
    Core::getInstance().run();
  }
  catch (...)
  {
    std::cerr << "Fatal error !" << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
