#include <vector>
#include <sstream>
#include "Pizza.hh"
#include "IKitchen.hh"
#include "NamedPipe.hh"
#include "kitcheninspector.hh"
#include "ui_kitcheninspector.h"

KitchenInspector::KitchenInspector(IReception* reception, QWidget *parent) :
    QDialog(parent), ui(new Ui::KitchenInspector), _reception(reception)

{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    this->refresh();
}

KitchenInspector::~KitchenInspector()
{
    delete ui;
}

void KitchenInspector::refresh(void)
{
    std::ostringstream *oss;
    this->_kitchens = this->_reception->getKitchenList();
    if (this->_kitchens.size() == 0)
        return;

    std::vector<Kitchen::Kitchen *>::iterator it;

    it = this->_kitchens.begin();
    for (; it != this->_kitchens.end(); ++it)
    {
        this->_reception->updateNbPizza(*it);

        size_t totalCook = (*it)->getTotalCook();
        size_t sleepingCook = (*it)->getSleeping();
        size_t activeCook = totalCook - sleepingCook;

        oss = new std::ostringstream;

        *oss << (*it)->getName() << " ";
        *oss << "Sleeping Cooks: " << sleepingCook << ", ";
        *oss << "Active Cooks: " << activeCook << ", ";
        *oss << "Cheese: " << (*it)->getIngredient(Pizza::Gruyere) << ", ";
        *oss << "Eggplant: " << (*it)->getIngredient(Pizza::Aubergine) << ", ";
        *oss << "Goat cheese: " << (*it)->getIngredient(Pizza::Chevre) << ", ";
        *oss << "Dough: " << (*it)->getIngredient(Pizza::Pate) << ", ";
        *oss << "Ham: " << (*it)->getIngredient(Pizza::Jambon) << ", ";
        *oss << "Love: " << (*it)->getIngredient(Pizza::Amour) << ", ";
        *oss << "Mushroom: " << (*it)->getIngredient(Pizza::Champignon) << ", ";
        *oss << "Steak: " << (*it)->getIngredient(Pizza::Steak) << ", ";
        *oss << "Tomate: " << (*it)->getIngredient(Pizza::Tomate);

        this->ui->listWidget->addItem(oss->str().c_str());

        delete (oss);
    }
}
