#ifndef JEFE1_H
#define JEFE1_H

#include "Enemigo1.h"
#include <QTimer>

class Jefe1 : public Enemigo1 {
    Q_OBJECT

public:
    Jefe1(QGraphicsView* view, QGraphicsItem* im = nullptr);
    void setSprite(bool direccion); // Sobrescribe el método setSprite
    void verificarColisionJugador(); // Sobrescribe el método verificarColisionJugador
    void setGolpeandoSprite();
    void verificarColisionJugador(Jugador* jugador);

    void moverEnLineaRecta(); // Método para mover al jefe en línea recta
    void actualizarSprite();
    void actualizarSpriteGolpe();



private:

    bool direccion = true;
    int contMov = 0;
    int contGolpe = 0;
    bool vidaReducida = false;
    bool movimientoHaciaAdelante = true;
    bool golpeando = false;

    QTimer* timerMovimiento;
    QTimer* spriteTimer;
    QTimer* spriteGolpeTimer;
    QTimer* timerColisionJugador;



};

#endif // JEFE1_H
