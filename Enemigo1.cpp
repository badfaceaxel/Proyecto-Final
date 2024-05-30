#include "Enemigo1.h"

Enemigo1::Enemigo1(QGraphicsView* view, QGraphicsItem* im)
    : Jugador(view, im) {

    // Inicializar la dirección de movimiento (true para moverse, false para detenerse)
    direccion = true; // Inicialmente se mueve hacia la izquierda

    // Cargar la hoja de sprites del enemigo
    spriteSheet.load(":/Imagenes/SpriteEnemigoADE.png");
    QPixmap spriteEnem1 = spriteSheet.copy(0, 96, 96, 96);
    setPixmap(spriteEnem1);
    setSprite(direccion);


    // Inicializar el temporizador para el movimiento
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Enemigo1::moverEnLineaRecta);
    timerMovimiento->start(50); // Ajusta el intervalo según sea necesario

    // Inicializar el temporizador para la animación del sprite
    spriteTimer = new QTimer(this);
    connect(spriteTimer, &QTimer::timeout, this, &Enemigo1::actualizarSprite);
    spriteTimer->start(360); // Ajusta el intervalo del temporizador según sea necesario

    moveBy(600, 35);
}

void Enemigo1::setSprite(bool direccion) {
    int spriteAncho = 96;
    int spriteAlto = 96;
    int spriteY = 0; // Usar el sprite de movimiento a la izquierda

    // Actualizar el sprite del enemigo
    QPixmap spriteEnem1 = spriteSheet.copy(contMov * spriteAncho, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteEnem1);
}

void Enemigo1::actualizarSprite() {
    // Incrementar el índice del sprite para la animación

    contMov++;
    if (contMov == 7) { // Hay 7 imágenes para la animación de movimiento
        contMov = 0;
    }
    setSprite(direccion);
}

void Enemigo1::moverEnLineaRecta() {
    // Mover el enemigo en línea recta hacia la izquierda
    if (direccion) {
        moveBy(-5, 0);

        // Detener el movimiento cuando el enemigo alcance la posición x = 200
        if (QGraphicsPixmapItem::x() <= 200) {
            direccion = false;
            timerMovimiento->stop();
            spriteTimer->stop();
        }
    }
}
