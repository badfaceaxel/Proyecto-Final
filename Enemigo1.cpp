#include "Enemigo1.h"

Enemigo1::Enemigo1(QGraphicsView* view, QGraphicsScene* scene, QGraphicsItem* im)
    : Jugador(view, im), scene(scene) {
    // Inicializar el temporizador para el movimiento
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Enemigo1::moverEnLineaRecta);
    timerMovimiento->start(50); // Ajusta el intervalo según sea necesario

    // Inicializar la dirección de movimiento (1 para derecha, -1 para izquierda)
    direccion = -1; // Inicialmente se mueve hacia la izquierda

    // Cargar la hoja de sprites del enemigo
    spriteSheet.load(":/Imagenes/SpriteEnemigoADE.png");

    // Establecer la posición inicial
    setPos(600, 200);

    // Establecer el sprite inicial
    setSprite();
}

void Enemigo1::setSprite() {
    int spriteAncho, spriteAlto, spriteX, spriteY;

    // Determinar el sprite basado en la dirección del enemigo
    if (direccion == 1) { // Hacia la derecha
        spriteAncho = 96;
        spriteAlto = 96;
        spriteX = 96;
        spriteY = 0;
    } else { // Hacia la izquierda
        spriteAncho = 96;
        spriteAlto = 96;
        spriteX = 96;
        spriteY = 96;
    }

    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, spriteAncho, spriteAlto);
    while (direccion == 1) {
        for (int i = 0; i < 8; i++) {
            sprite = spriteSheet.copy(spriteX * i, spriteY, spriteAncho, spriteAlto);
        }
    }
    while (direccion == -1) {
        for (int i = 0; i < 7; i++) {
            sprite = spriteSheet.copy(spriteX * i, spriteY, spriteAncho, spriteAlto);
        }
    }
    setPixmap(sprite);
}

void Enemigo1::moverEnLineaRecta() {
    // Mover el enemigo en línea recta
    moveBy(5 * direccion, 0);

    // Cambiar la dirección cuando el enemigo alcance los límites del intervalo
    if ((QGraphicsPixmapItem::x() < 200 && direccion == -1) || (QGraphicsPixmapItem::x() > 600 && direccion == 1)) {
        direccion *= -1;
        setSprite();
    }
}
