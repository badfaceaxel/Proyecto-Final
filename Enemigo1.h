#ifndef ENEMIGO1_H
#define ENEMIGO1_H

#include "Jugador.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

class Enemigo1 : public Jugador {
    Q_OBJECT

public:
    Enemigo1(QGraphicsView* view, QGraphicsItem* im = nullptr);
    void setSprite(bool direccion); // Declaración del método setSprite
    int contMov = 0;
private slots:
    void moverEnLineaRecta();
    void actualizarSprite();

private:
    QTimer* timerMovimiento;
    QTimer* spriteTimer;
    bool direccion = false; // 1 para derecha, -1 para izquierda
    QGraphicsScene* scene; // Referencia a la escena

protected:
    QPixmap spriteEnem1;

};

#endif // ENEMIGO1_H
