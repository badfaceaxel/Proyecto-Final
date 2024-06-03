#ifndef ENEMIGO2_H
#define ENEMIGO2_H

#include "Jugador.h"

class Enemigo2 : public Jugador{
    Q_OBJECT

public:
    //void setSprite(bool lanzandoDardo);
    //void actualizarAnimacion();

    Enemigo2(QGraphicsView* view, QGraphicsItem* im = nullptr);

    void actualizarPosicion();
    void lanzarDardo(const QPointF& posicionJugador);
    //aaaaaaaaa
    void actualizarAnimacionLanzar();
    void lanzarDardoReal(const QPointF& posicionJugador);

    QPointF obtenerPosicion() const;
    void setJugador(Jugador* jugador);

    void verificarColisionJugador();

    void rotarSpriteDardo(qreal angulo);

private:
    //bool mov = false;

    bool dardoLanzado = false;
    bool dardoHaciaLaDerecha = true;

    QTimer* timerAnimacion = nullptr;
    int contadorAnimacion = 0;


    QGraphicsPixmapItem* dardo = nullptr;
    Jugador* jugador = nullptr;
    QTimer* timerVerificarDistancia = nullptr;

    int direccionDardo = 1;
    bool vidaReducida = false;
    Jugador* jugadorObj = nullptr;

signals:
    void eliminarEnemigo();
};

#endif // ENEMIGO2_H
