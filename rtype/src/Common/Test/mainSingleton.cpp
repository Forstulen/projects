#include			<iostream>
#include			"Singleton.hpp"

class				Test : public Tools::Singleton<Test>
{

  friend class Tools::Singleton<Test>;

private:

  Test() {}
  ~Test() {}

};

int			main()
{
  {
    Test		&toto = Test::getInstance();

    std::cout << "bim" << std::endl;
  }
  {
    std::cout << "bam" << std::endl;

    Test		&toto = Test::getInstance();

    std::cout << "boom" << std::endl;
    Test::getInstance();
    Tools::Singleton<Test>::getInstance();
  }

  Test::getInstance();
  return (0);
}
