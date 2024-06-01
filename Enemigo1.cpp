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

    // Inicializar el temporizador para la animación del sprite de golpe
    spriteGolpeTimer = new QTimer(this);
    connect(spriteGolpeTimer, &QTimer::timeout, this, &Enemigo1::actualizarSpriteGolpe);

    // Inicializar el temporizador para verificar la colisión con el Jugador
    timerColisionJugador = new QTimer(this);
    connect(timerColisionJugador, &QTimer::timeout, this, &Enemigo1::verificarColisionJugador);
    timerColisionJugador->start(50); // Ajusta el intervalo según sea necesario

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
    jugadorObj->setFocus();
    setSprite(direccion);
}

void Enemigo1::moverEnLineaRecta() {
    // Mover el enemigo en línea recta hacia la izquierda
    if (direccion) {
        moveBy(-5, 0);
        jugadorObj->setFocus();
        // Detener el movimiento cuando el enemigo alcance la posición x = 200
        if (QGraphicsPixmapItem::x() <= 200) {
            direccion = false;
            timerMovimiento->stop();
            spriteTimer->stop();
        }
    }
}

//GOLPE

void Enemigo1::setGolpeandoSprite() {
    int spriteAncho = 96;
    int spriteAlto = 96;
    int spriteY = 96; // Usar el sprite de golpe

    // Actualizar el sprite del enemigo
    QPixmap spriteEnem1 = spriteSheet.copy(contGolpe * spriteAncho, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteEnem1);
}

void Enemigo1::actualizarSpriteGolpe() {
    // Incrementar el índice del sprite para la animación de golpe
    contGolpe++;
    if (contGolpe == 5) { // Hay 5 imágenes para la animación de golpe
        contGolpe = 0;
        golpeando = false; // Termina la animación de golpe
        spriteGolpeTimer->stop(); // Detiene el temporizador
        jugadorObj->setFocus();
    }

    setGolpeandoSprite();
}

//Reconocimiento

void Enemigo1::verificarColisionJugador() {
    // Verificar si el Enemigo1 colisiona con el Jugador
    if (collidesWithItem(jugadorObj)) {
        // Activar el sprite de golpe
        golpeando = true;
        spriteGolpeTimer->start(100); // Inicia el temporizador para la animación de golpe
        setGolpeandoSprite(); // Actualiza el sprite para la primera imagen de golpe

        // Detiene el movimiento temporalmente
        timerMovimiento->stop();
        spriteTimer->stop();
    }
}

void Enemigo1::setJugador(Jugador* jugador) {
    jugadorObj = jugador;
}
