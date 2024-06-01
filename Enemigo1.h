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
    void setGolpeandoSprite();//para actualizar el sprite de golpe
    void verificarColisionJugador();

    void setJugador(Jugador* jugador); // metodo para establecer el objeto Jugador

private slots:
    void moverEnLineaRecta();
    void actualizarSprite();
    void actualizarSpriteGolpe(); // actualizar el sprite de golpe


private:
    QTimer* timerMovimiento;
    QTimer* spriteTimer;
    QTimer* spriteGolpeTimer;
    QTimer* timerColisionJugador;

    int contMov = 0;
    int contGolpe = 0;
    bool golpeando = false;

    bool direccion = false; // 1 para derecha, -1 para izquierda
    QGraphicsScene* scene; // Referencia a la escena

    Jugador* jugadorObj = nullptr; // Puntero al objeto Jugador
protected:
    QPixmap spriteEnem1;

};

#endif // ENEMIGO1_H
