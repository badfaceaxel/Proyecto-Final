#ifndef JEFE1_H
#define JEFE1_H

#include "Enemigo1.h"
#include <QTimer>

class Jefe1 : public Enemigo1 {
    Q_OBJECT

public:
    Jefe1(QGraphicsView* view, QGraphicsItem* im = nullptr);
    void setGolpeandoSpriteJefe();
    void verificarColisionJugador(Jugador* jugador);
    void setSprite(bool direccion);
    void moverEnLineaRecta(); // Método para mover al jefe en línea recta
    void actualizarSpriteJefe();
    void actualizarSpriteGolpeJefe();
    void setJugador(Jugador* jugador);

protected:
           // Sobrescribe el método setSprite


private:

    bool direccion = true;
    int contMov = 0;
    int contaGolpe = 0;
    bool vidaReducida = false;
    bool movimientoHaciaAdelante = true;
    bool golpeando = false;
    bool jugadorReconocido = false;

    QTimer* timerMovimiento;
    QTimer* spriteTimer;
    QTimer* spriteGolpeTimer;
    QTimer* timerColisionJugador;

    QTimer* timerRetardoGolpe;



};

#endif // JEFE1_H
