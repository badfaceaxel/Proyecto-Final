#include "Enemigo1.h"

Enemigo1::Enemigo1(QGraphicsView* view, QGraphicsItem* im)
    : Jugador(view, im) {

    // Inicializar la dirección de movimiento (true para moverse, false para detenerse)
    direccion = false;

    // Cargar la hoja de sprites del enemigo
    spriteSheet.load(":/Media/SpriteEnemigoADE.png");
    QPixmap spriteEnem1 = spriteSheet.copy(0, 96, 96, 96);
    setPixmap(spriteEnem1);
    setSpriteEnem(direccion);

    //qDebug() << posicionX << posicionY;
    //(posicionX, posicionY);

    // Inicializar el temporizador para el movimiento
    timerMovimiento = new QTimer(this);
    connect(timerMovimiento, &QTimer::timeout, this, &Enemigo1::moverEnLineaRectaEnem);

    // Inicializar el temporizador para la animación del sprite
    spriteTimer = new QTimer(this);
    connect(spriteTimer, &QTimer::timeout, this, &Enemigo1::actualizarSpriteEnem);
    spriteTimer->start(360); // Ajusta el intervalo del temporizador según sea necesario

    // Inicializar el temporizador para la animación del sprite de golpe
    spriteGolpeTimer = new QTimer(this);
    connect(spriteGolpeTimer, &QTimer::timeout, this, &Enemigo1::actualizarSpriteGolpeEnem);

    // Inicializar el temporizador para verificar la colisión con el Jugador
    timerColisionJugador = new QTimer(this);
    connect(timerColisionJugador, &QTimer::timeout, this, &Enemigo1::verificarColisionJugadorEnem);
    timerColisionJugador->start(50); // Ajusta el intervalo según sea necesario


    //moveBy(600, 35);
}

void Enemigo1::establecerPosicionInicial(qreal posicionX, qreal posicionY) {
    //qDebug() << "Estableciendo posición inicial:" << posicionX << posicionY;
    setPos(posicionX, posicionY);
    //qDebug() << "Posición establecida:" << pos();
}

void Enemigo1::setSpriteEnem(bool direccion) {
    int spriteAncho = 96;
    int spriteAlto = 96;
    int spriteY = 0; // Usar el sprite de movimiento a la izquierda

    // Actualizar el sprite del enemigo
    QPixmap spriteEnem1 = spriteSheet.copy(contMov * spriteAncho, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteEnem1);
}

void Enemigo1::actualizarSpriteEnem() {
    // Incrementar el índice del sprite para la animación

    contMov++;
    if (contMov == 7) { // Hay 7 imágenes para la animación de movimiento
        contMov = 0;
    }
    jugadorObj->setFocus();
    setSpriteEnem(direccion);
}

void Enemigo1::moverEnLineaRectaEnem() {
    // Mover el enemigo en línea recta hacia la izquierda
    setPos(QGraphicsPixmapItem::x() - 5, QGraphicsPixmapItem::y()); // Mover hacia la izquierda

    // Obtener la posición actual del enemigo
    qreal posicionActualX = QGraphicsPixmapItem::x();
    qreal posicionInicialX = posicionActualX; // Guardar la posición inicial
    //qDebug() << posicionActualX;
    //qDebug() << posicionInicialX;
    // Invertir la dirección cuando el enemigo alcanza la posición límite
    if (posicionActualX <= posicionInicialX - 200) {
        timerMovimiento->stop();
        spriteTimer->stop();
    }
}

//GOLPE

void Enemigo1::setGolpeandoSpriteEnem() {

    //qDebug() << "entro";
    int spriteAncho = 96;
    int spriteAlto = 96;
    int spriteY = 96; // Usar el sprite de golpe

    // Actualizar el sprite del enemigo
    //qDebug()<< contGolpe;
    QPixmap spriteEnem1 = spriteSheet.copy(contGolpeEnemigo * spriteAncho, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteEnem1);

}

void Enemigo1::actualizarSpriteGolpeEnem() {
    // Incrementar el índice del sprite para la animación de golpe

    contGolpeEnemigo++;
    if (contGolpeEnemigo == 5) { // Hay 5 imágenes para la animación de golpe
        contGolpeEnemigo = 0;
        golpeando = false; // Termina la animación de golpe
        spriteGolpeTimer->stop(); // Detiene el temporizador
        jugadorObj->setFocus();
    }
    setGolpeandoSpriteEnem();
}

//Reconocimiento

void Enemigo1::verificarColisionJugadorEnem() {
    // Verificar si el Enemigo1 colisiona con el Jugador
    if (collidesWithItem(jugadorObj)) {
        // Activar el sprite de golpe
        golpeando = true;
        spriteGolpeTimer->start(100); // Inicia el temporizador para la animación de golpe
        setGolpeandoSpriteEnem(); // Actualiza el sprite para la primera imagen de golpe

        // Detiene el movimiento temporalmente
        timerMovimiento->stop();
        spriteTimer->stop();

        // Reducir la vida del jugador solo si no se ha reducido antes en este encuentro
        if (!vidaReducida) {
            jugadorObj->disminuirVida(5);
            vidaReducida = true; // Establecer la bandera a true después de reducir la vida
        }
    } else {
        // Si no hay colisión, restablecer la bandera para el próximo encuentro
        vidaReducida = false;
    }
}

void Enemigo1::setJugador(Jugador* jugador) {
    jugadorObj = jugador;
}

Enemigo1::~Enemigo1() {
    // Liberar la memoria ocupada por spriteSheet
    spriteSheet = QPixmap();
}

void Enemigo1::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug() << "Hola";

}

bool Enemigo1::eventFilter(QObject *obj, QEvent *event) {
    //qDebug() << "2.0HOLA";
    return false;

}

void Enemigo1::actualizarCaida() {
    //qDebug() << "hola";
}
