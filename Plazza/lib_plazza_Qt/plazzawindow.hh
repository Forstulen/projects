#ifndef PLAZZAWINDOW_HH
#define PLAZZAWINDOW_HH

#include <QMainWindow>
#include <QKeyEvent>
#include "IReception.hh"

namespace Ui {
    class PlazzaWindow;
}

class PlazzaWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlazzaWindow(IReception *reception, QWidget *parent = 0);
    ~PlazzaWindow();

public:
    Ui::PlazzaWindow* getUi(void) const { return (this->ui); }
    void keyPressEvent(QKeyEvent *);
    void connectSignalSlot(void);
    void assemblyCommand(std::string const &);

public slots:
    void sendCommand(void);
    void commandMargarita(void);
    void commandRegina(void);
    void commandAmericaine(void);
    void commandFantasia(void);
    void updateCommand(void);
    void openInspector(void);

private:
    Ui::PlazzaWindow *ui;
    IReception* _reception;
    std::string _command;
};

#endif // PLAZZAWINDOW_HH
