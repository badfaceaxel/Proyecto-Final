#ifndef MENUINICIO_H
#define MENUINICIO_H

#include <QWidget>
#include <QTimer>
#include "Jugador.h"

namespace Ui {
class MenuInicio;
}

class MenuInicio : public QWidget
{
    Q_OBJECT

public:
    explicit MenuInicio(QWidget *parent = nullptr);
    ~MenuInicio();

private:
    Ui::MenuInicio *ui;
};

#endif // MENUINICIO_H
