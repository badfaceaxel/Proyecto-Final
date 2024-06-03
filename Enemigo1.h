#ifndef ENEMIGO1_H
#define ENEMIGO1_H

#include "Jugador.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QRandomGenerator>

class Enemigo1 : public Jugador {
    Q_OBJECT

public:
    Enemigo1(QGraphicsView* view, QGraphicsItem* im = nullptr);
    void setSprite(bool direccion); // Declaración del método setSprite
    void setGolpeandoSprite();//para actualizar el sprite de golpe
    void verificarColisionJugador();

    void setJugador(Jugador* jugador); // metodo para establecer el objeto Jugador

    //instancias
    void establecerPosicionInicial(qreal posicionX, qreal posicionY);
    void inicializarTemporizador();
    QTimer* timerMovimiento;
    static QList<Enemigo1*> crearEnemigos(QGraphicsView* view, Jugador* jugador, QGraphicsScene* scene);

    ~Enemigo1();
    //void liberarMemoriaSprite();
private slots:
    void moverEnLineaRecta();
    void actualizarSprite();
    void actualizarSpriteGolpe(); // actualizar el sprite de golpe


private:

    QTimer* spriteTimer;
    QTimer* spriteGolpeTimer;
    QTimer* timerColisionJugador;

    int contMov = QRandomGenerator::global()->bounded(7);//cambiar depronto
    int contGolpeEnemigo = 0;
    bool golpeando = false;

    bool direccion = true;
    QGraphicsScene* scene; // Referencia a la escena

    Jugador* jugadorObj = nullptr; // Puntero al objeto Jugador

    //VIDAAAa
    bool vidaReducida = false;



protected:
    QPixmap spriteEnem1;

signals:
    void eliminarEnemigo();
};

#endif // ENEMIGO1_H
