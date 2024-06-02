#ifndef ENEMIGO2_H
#define ENEMIGO2_H

#include "Jugador.h"

class Enemigo2 : public Jugador
{
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



private:
    //bool mov = false;

    bool dardoLanzado = false;

    QTimer* timerAnimacion = nullptr;
    int contadorAnimacion = 0;


    QGraphicsPixmapItem* dardo = nullptr;
    Jugador* jugador = nullptr;
    QTimer* timerVerificarDistancia = nullptr;

    int direccionDardo = 1;
};

#endif // ENEMIGO2_H
