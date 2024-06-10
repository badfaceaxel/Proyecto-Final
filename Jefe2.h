#ifndef JEFE2_H
#define JEFE2_H

#include "Jugador.h"
#include "Enemigo2.h"
#include <QTimer>
#include <QPixmap>
#include <QtMath>
#include <QTime>


class Jefe2 : public Enemigo2 {
    Q_OBJECT

public:
    Jefe2(QGraphicsView* view, QGraphicsItem* im = nullptr);

    void actualizarPosicion();
    void lanzarFlecha(const QPointF& posicionJugador);
    void setAnimacionLanzamientoFlechaSprite();
    void actualizarAnimacionLanzarFlecha();
    void lanzarFlechaReal(const QPointF& posicionJugador);

    void golpearJugador();
    void setGolpeandoSprite();
    void actualizarAnimacionGolpe();

    QPointF obtenerPosicion() const;
    void setJugador(Jugador* jugador);

private:
    QPixmap spriteSheetFlecha;
    QPixmap spriteSheetGolpe;
    int contadorAnimacionFlecha = 0;
    int contadorAnimacionGolpe = 0;
    QTimer* timerAnimacionFlecha = nullptr;
    QTimer* timerAnimacionGolpe = nullptr;
    QGraphicsPolygonItem* flecha = nullptr;
    bool golpeando = false;
    bool flechaLanzada = false;
    bool flechaHaciaLaDerecha = true;
    QTimer* timerVerificarDistancia = nullptr;
    Jugador* jugadorObj = nullptr;
    bool vidaReducida = false;

    QTime tiempoUltimoGolpe;
    bool puedeDisparar = true;

};

#endif // JEFE2_H
