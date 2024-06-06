#include "Jefe1.h"

Jefe1::Jefe1(QGraphicsView* view, QGraphicsItem* im)
    : Enemigo1(view, im)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    spriteSheet.load(":/Imagenes/SpriteJefeA.png");
    QPixmap spriteJefe1 = spriteSheet.copy(0, 128, 128, 128);
    setPixmap(spriteJefe1);
    setSprite(movimientoHaciaAdelante);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Jefe1::moverEnLineaRecta);
    timerMovimiento->start(50);

    spriteTimer = new QTimer(this);
    connect(spriteTimer, &QTimer::timeout, this, &Jefe1::actualizarSprite);
    spriteTimer->start(360);

    spriteGolpeTimer = new QTimer(this);
    connect(spriteGolpeTimer, &QTimer::timeout, this, &Jefe1::actualizarSpriteGolpe);

    timerColisionJugador = new QTimer(this);
    connect(timerColisionJugador, &QTimer::timeout, this, [this]() {
        verificarColisionJugador(this->jugadorObj);
    });
    timerColisionJugador->start(50);
}

void Jefe1::setSprite(bool direccion)
{
    int spriteAncho = 128;
    int spriteAlto = 128;
    int spriteY;

    if (direccion) {
        spriteY = 0; // Sprites de movimiento hacia adelante
    } else {
        spriteY = 128; // Sprites de movimiento hacia atrás
    }

    QPixmap spriteJefe1 = spriteSheet.copy(contMov * spriteAncho, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteJefe1);
}

void Jefe1::moverEnLineaRecta()
{
    static bool avanzando = true;

    if (avanzando) {
        setPos(QGraphicsPixmapItem::x() + 5, QGraphicsPixmapItem::y());
        movimientoHaciaAdelante = true;
    } else {
        setPos(QGraphicsPixmapItem::x() - 5, QGraphicsPixmapItem::y());
        movimientoHaciaAdelante = false;
    }

    setSprite(movimientoHaciaAdelante);

    if (avanzando && QGraphicsPixmapItem::x() >= 600) {
        avanzando = false;
    } else if (!avanzando && QGraphicsPixmapItem::x() <= 400) {
        avanzando = true;
    }
}

void Jefe1::actualizarSprite()
{
    contMov++;
    if (contMov == 8) {
        contMov = 0;
    }
    setSprite(movimientoHaciaAdelante);
}

void Jefe1::actualizarSpriteGolpe()
{
    contGolpe++;
    if (contGolpe == 4) {
        contGolpe = 0;
        golpeando = false;
        spriteGolpeTimer->stop();
        jugadorObj->setFocus();
        //Para poder volver a moverse
        timerMovimiento->start(50);
        spriteTimer->start(360);
    }
    setGolpeandoSprite();
}

void Jefe1::setGolpeandoSprite() {
    int spriteAncho = 128;
    int spriteAlto = 128;
    int spriteY = 256; // Usar el sprite de golpe

    QPixmap spriteJefe1 = spriteSheet.copy(contGolpe * spriteAncho, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteJefe1);

}

void Jefe1::verificarColisionJugador(Jugador* jugador)
{
    if (collidesWithItem(jugador)) {
        timerMovimiento->stop();
        spriteTimer->stop();

        golpeando = true;
        spriteGolpeTimer->start(200); // Inicia el temporizador para la animación de golpe
        setGolpeandoSprite();


        if (!vidaReducida) {
            jugador->disminuirVida(8);
            vidaReducida = true;
        }
    } else {
        vidaReducida = false;
    }
}
