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

    void setJugador(Jugador* jugador); // metodo para establecer el objeto Jugador

    //instancias
    void establecerPosicionInicial(qreal posicionX, qreal posicionY);
    void inicializarTemporizador();
    QTimer* timerMovimiento;


    ~Enemigo1();
    //void liberarMemoriaSprite();


private slots:
    void moverEnLineaRecta();
    void actualizarSprite();
    void actualizarSpriteGolpe(); // actualizar el sprite de golpe

    void setSprite(bool direccion);
    void setGolpeandoSprite();
    void verificarColisionJugador();

private:

    QTimer* spriteTimer;
    QTimer* spriteGolpeTimer;
    QTimer* timerColisionJugador;

    int contMov = QRandomGenerator::global()->bounded(7);
    int contGolpeEnemigo = 0;

    bool golpeando = false;
    bool direccion = true;


    //VIDAAAa
    bool vidaReducida = false;



protected:
    QPixmap spriteEnem1;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
    void actualizarCaida() override;

    Jugador* jugadorObj = nullptr; // Puntero al objeto Jugador
    QGraphicsScene* scene; // Referencia a la escena

signals:
    void eliminarEnemigo();
};

#endif // ENEMIGO1_H
