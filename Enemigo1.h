#ifndef ENEMIGO1_H
#define ENEMIGO1_H

#include "Jugador.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

class Enemigo1 : public Jugador {
    Q_OBJECT

public:
    Enemigo1(QGraphicsView* view, QGraphicsScene* scene, QGraphicsItem* im = nullptr);
    void setSprite(); // Declaración del método setSprite

private slots:
    void moverEnLineaRecta();

private:
    QTimer* timerMovimiento;
    int direccion; // 1 para derecha, -1 para izquierda
    QGraphicsScene* scene; // Referencia a la escena
};

#endif // ENEMIGO1_H
