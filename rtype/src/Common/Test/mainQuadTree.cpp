#include		<list>
#include		<map>

#include		"AGameObject.hpp"
#include		"QuadTree.hpp"
#include		"AssetManager.hpp"
#include		"LoaderManager.hpp"

int			main()
{
  QuadTree<Asset::AGameObject> quad_(4, 0, 0, 800, 800);
  std::map<int, Asset::AGameObject *> obj;
  std::list<Asset::AGameObject *> *list = NULL;
  int			pos = 0;

  if (!RTDB::Database::getInstance().fillFromFile("../../../resource/bdd.rtdb"))
    {
      std::cout << "Error : Cannot load database !" << std::endl;
      return 1;
    }
  if (!Loader::LoaderManager::getInstance().loadObjects())
    std::cout << " Fail to load Monster" << std::endl;
  Asset::AssetManager::getInstance().loadAssets();
  for (int count = 0; count < 2; ++count)
    {
      obj[count] = dynamic_cast<Asset::AGameObject*>(Loader::LoaderManager::getInstance().getObject("MonsterObject1"));
      obj[count]->initObject(pos, pos, 0.05, 50, 50, 0, false, NULL);
      obj[count]->setId(count);
    }
  list = quad_.listingOnCollisionObject(obj);
  for (std::list<Asset::AGameObject *>::iterator it = list->begin(); it != list->end(); ++it)
    std::cout << "Number of Collision " << (*it)->getId() << std::endl;
  return (0);
}
