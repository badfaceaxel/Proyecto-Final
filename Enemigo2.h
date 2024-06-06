#ifndef ENEMIGO2_H
#define ENEMIGO2_H

#include "Jugador.h"

class Enemigo2 : public Jugador{
    Q_OBJECT

public:

    Enemigo2(QGraphicsView* view, QGraphicsItem* im = nullptr);

    void lanzarDardo(const QPointF& posicionJugador);
    void setAnimacionLanzamientoSprite();
    void actualizarAnimacionLanzar();
    void lanzarDardoReal(const QPointF& posicionJugador);


    void setJugador(Jugador* jugador);
    bool yaEliminado = false;

private:
    QPointF obtenerPosicion() const;
    void actualizarPosicion();

    bool dardoLanzado = false;
    bool dardoHaciaLaDerecha = true;

    QTimer* timerAnimacion = nullptr;
    int contadorAnimacion = 0;


    QGraphicsPolygonItem* dardo = nullptr;
    Jugador* jugador = nullptr;
    QTimer* timerVerificarDistancia = nullptr;

    int direccionDardo = 1;
    bool vidaReducida = false;



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void actualizarCaida() override;

    Jugador* jugadorObj = nullptr;


signals:
    void eliminarEnemigo();
};

#endif // ENEMIGO2_H
