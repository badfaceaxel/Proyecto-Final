#include "Jefe1.h"

Jefe1::Jefe1(QGraphicsView* view, QGraphicsItem* im)
    : Enemigo1(view, im)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    spriteSheet.load(":/Imagenes/SpriteJefeA.png");
    QPixmap spriteJefe1 = spriteSheet.copy(0, 0, 128, 128);
    setPixmap(spriteJefe1);
    setSprite(movimientoHaciaAdelante);

    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Jefe1::moverEnLineaRecta);
    timerMovimiento->start(50);

    spriteTimer = new QTimer(this);
    connect(spriteTimer, &QTimer::timeout, this, &Jefe1::actualizarSpriteJefe);
    spriteTimer->start(360);

    spriteGolpeTimer = new QTimer(this);
    connect(spriteGolpeTimer, &QTimer::timeout, this, &Jefe1::actualizarSpriteGolpeJefe);

    timerColisionJugador = new QTimer(this);
    connect(timerColisionJugador, &QTimer::timeout, this, [=]() { verificarColisionJugador(jugadorObj); });
    timerColisionJugador->start(50); // Ajusta el intervalo según sea necesario

    // Inicializamos la bandera de reconocimiento del jugador
    jugadorReconocido = false;
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

void Jefe1::actualizarSpriteJefe()
{
    contMov++;
    if (contMov == 8) {
        contMov = 0;
    }
    setSprite(movimientoHaciaAdelante);
}

void Jefe1::actualizarSpriteGolpeJefe()
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
        // Reiniciamos la bandera de reconocimiento del jugador
        jugadorReconocido = false;
    }
    setGolpeandoSpriteJefe();
}

void Jefe1::setGolpeandoSpriteJefe() {
    int spriteAncho = 128;
    int spriteAlto = 128;
    int spriteY = 256; // Usar el sprite de golpe
    //qDebug()<< contGolpe;
    QPixmap spriteJefe1 = spriteSheet.copy(contGolpe * spriteAncho, spriteY, spriteAncho, spriteAlto);

    setPixmap(spriteJefe1);
}

void Jefe1::verificarColisionJugador(Jugador* jugador)
{
    if (collidesWithItem(jugador) && !jugadorReconocido) {
        // Marcar que el jugador ha sido reconocido para evitar que se repita el golpe
        jugadorReconocido = true;

        golpeando = true;
        spriteGolpeTimer->start(300); // Inicia el temporizador para la animación de golpe
        setGolpeandoSpriteJefe();

        timerMovimiento->stop();
        spriteTimer->stop();

        if (!vidaReducida) {
            jugador->disminuirVida(8);
            vidaReducida = true;
        }
    } else {
        vidaReducida = false;
    }
}

void Jefe1::setJugador(Jugador* jugador) {
    jugadorObj = jugador;
}
