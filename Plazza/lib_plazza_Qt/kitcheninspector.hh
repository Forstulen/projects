#ifndef KITCHENINSPECTOR_HH
#define KITCHENINSPECTOR_HH

#include <QDialog>
#include "IReception.hh"
#include "Kitchen.hh"

namespace Ui {
    class KitchenInspector;
}

class KitchenInspector : public QDialog
{
    Q_OBJECT

public:
    explicit KitchenInspector(IReception* reception, QWidget *parent = 0);
    ~KitchenInspector();

public:
    void refresh(void);

private:
    Ui::KitchenInspector *ui;
    IReception* _reception;
    std::vector<Kitchen::Kitchen *> _kitchens;
};

#endif // KITCHENINSPECTOR_HH
