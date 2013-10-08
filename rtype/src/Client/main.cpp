#include "Database.hpp"
#include "App/CoreRTYPE.hpp"
#include "StateManager.hpp"
#include "LoaderManager.hpp"

int main(int ac, char **av)
{
  if (!RTDB::Database::getInstance().fillFromFile("../../resource/bdd.rtdb"))
  {
    std::cerr << "Error : Cannot load database !" << std::endl;
    return 1;
  }
  try
  {
  Loader::LoaderManager::getInstance().loadObjects();
  }
  catch (...)
  {
	std::cerr << "Error : Cannot load dynamic objects !" << std::endl;
  }
  std::cerr << " Game Launched "  << std::endl;
  try
  {
    App::CoreRTYPE::getInstance().run();
  }
  catch (...)
  {
    std::cerr << "Fatal Error !" << std::endl;
    return 1;
  }
  return 0;
}
