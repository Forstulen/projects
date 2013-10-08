//
// Reception.hh for plazza in /home/allaux_c//rendu/cpp/plazza-2014-tholim_r
//
// Made by chanh allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Thu Apr  7 17:53:36 2011 chanh allaux
// Last update Sun Apr 17 22:24:38 2011 romain tholimet
//

#ifndef					__RECEPTION_HH_
# define				__RECEPTION_HH_

#include				<iostream>
#include				<vector>
#include				<fstream>

#include				"Thread.hh"
#include				"Kitchen.hh"
#include				"NamedPipe.hh"
#include				"IReception.hh"
#include				"Mutex.hh"

class ILibrary;

namespace				Reception
{
  typedef enum				e_typeCommande
    {
      PIZZA = 0,
      REFRESH,
      DEAD,
      THROW
    }					e_typeCommande;

  class					Reception : public IReception
  {
    size_t				_coefCook;
    size_t				_nbrCook;
    size_t				_timePopFood;
    std::vector<Kitchen::Kitchen *>	_kitchens;
    NamedPipe				*_pipeInput;
    Thread::Thread			_threadForPizza;
    bool				_flag;
    Mutex				_mutex;
    Mutex				_update;
    ILibrary*				_lib;
    CondVar				*_updPizza;
    std::fstream			_logFile;

  public:
    virtual ~Reception();
    Reception(size_t, size_t, size_t, ILibrary*);

  private:
    void				repartPizzaList(std::vector<const Pizza::Pizza*>*);
    void				repartPizza(const Pizza::Pizza*);
    void				openKitchen(void);
    void				sendPizzaToKitchen(Kitchen::Kitchen*, const Pizza::Pizza*);
    void				openKitchen(const Pizza::Pizza*);
    int					updateKitchen(int);
    void				workFinished();
    int					killKitchen(int);
    void				killReception(int);

  public:
    virtual void			updateNbPizza(const Kitchen::Kitchen*);
    int					checkInformations(int);
    virtual void			receiveCommand(std::string const &);
    bool				getFlag(void) const;
    NamedPipe				*getPipe(void) const;
    void				log(const Pizza::Pizza* , std::string const &);
    void				log(std::string const &);
    virtual std::vector<Kitchen::Kitchen *> const &	getKitchenList(void);
  };

  void*					receivePizza(void*);
}


#endif
