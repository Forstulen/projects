//
// Kitchen.hh for plazza in /home/benram_s//Desktop/program/cpp/plazza-2014-tholim_r/sources/plazza
//
// Made by soufien benramdhane
// Login   <benram_s@epitech.net>
//
// Started on  Fri Apr  8 17:46:47 2011 soufien benramdhane
// Last update Sun Apr 17 21:57:29 2011 romain tholimet
//

#ifndef			__KITCHEN_HH__
#define			__KITCHEN_HH__

#include		<map>
#include		<string>

#include		"SafeQueue.hpp"
#include		"Thread.hh"
#include		"Pizza.hh"
#include		"Mutex.hh"
#include		"CondVar.hpp"
#include		"IKitchen.hh"

class					NamedPipe;
class					IReception;

namespace				Kitchen
{
  typedef union				u_infoSerial
  {
    int					info[22];
    char				serial[88];
  }					u_infoSerial;

  typedef enum				e_infoType
    {
      COOKING = 0,
      PATE,
      TOMATE,
      GRUYERE,
      JAMBON,
      CHAMPIGNON,
      STEAK,
      AUBERGINE,
      CHEVRE,
      AMOUR,
      MAX,
      PIZZAS
    }					e_infoType;

  class					Kitchen;

  class					Stock
  {
    size_t				_kindOfIngredient;
    size_t				_popFood;
    std::map<size_t, size_t>		_stock;
    Thread::Thread			_delivery;
    Mutex				_mutex;

  public:
    Stock(size_t repop);
    ~Stock();

  public:
    bool				pickUp(Pizza::Ingredient ingredient);
    void				refill(void);

  public:
    void				setNumberOf(Pizza::Ingredient ingredient, int nbr);

  public:
    size_t				getNumberOf(Pizza::Ingredient ingredient) const;
  };

  // tramplopline
  void*					doRefill(void *arg);

  class					Cook;

  class					Kitchen : public IKitchen
  {
    size_t				_nbPizza;
    size_t				_coefTime;
    size_t				_nbrCook;
    size_t				_popFood;
    std::string				_name;
    size_t				_pid;
    size_t				_sleepingCook;

  private:
    NamedPipe				*_pipeInput;
    NamedPipe				*_pipeOutput;

  private:
    SafeQueue<int>			_queuePizza;
    std::vector<Cook *>			_cook;
    Stock				_stock;

  private:
    Mutex				_mutex;
    CondVar				_condCook;
    CondVar				_condKitchen;

  public:
    Kitchen(size_t pid, size_t coefTime, size_t nbrCook, size_t popFood, NamedPipe *pipe);
    virtual ~Kitchen();

  public:
    void				startCooking(void);
    void				receiveCommand(void);
    void				packPizza(int serial);
    void				iAmDead(void);
    void				youAreDead(void);

  public:
    Cook				*getCook(void);
    Stock const &			getStock(void) const;
    NamedPipe*				getNamedPipe(void) const;
    size_t				getNbPizza(void) const;
    virtual size_t			getIngredient(Pizza::Ingredient ingredient) const;
    virtual size_t			getCookSleeping() const;
    virtual size_t			getSleeping() const;
    virtual std::string const		&getName() const;
    virtual size_t			getTotalCook(void) const;
    size_t				getPid() const;

  public:
    void				setNumberOf(Pizza::Ingredient ingredient, int nbr);
    void				setCookSleeping(int nbr);
    void				setNbPizza(int nbr);

  private:
    void				executeOrder(void);
    bool				stillCookWorking(void) const;
    int					typeCommand(int serial) const;
    void				typeManagement(int serial);
    void				sendInfo(void) const;

  private:
    Cook				*getFreeCook(void) const;

  private:
    void				decremPizza(void);
  };

  class					Cook : public Thread::Thread
  {
    Kitchen				*_kitchen;
    int					_serial;

  public:
    Cook(Kitchen *kitchen);
    ~Cook();

  public:
    void				setPizza(int serial);

  public:
    Kitchen				*getKitchen(void) const;
    int					getPizza(void) const;
  };

  //Trampoline pour lancer les methodes des Cuisiniers
  void					*doPizza(void *arg);
  void					*dispatchPizza(void *arg);
}

#endif
