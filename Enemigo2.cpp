#include "Enemigo2.h"
#include <QTimer>
#include <QPixmap>
#include <QtMath>

Enemigo2::Enemigo2(QGraphicsView* view, QGraphicsItem* im)
    : Jugador(view, im), dardoLanzado(false), contadorAnimacion(0)
{
    // Inicialización del enemigo
    setFlag(QGraphicsItem::ItemIsFocusable, false);

    // Cargar sprite del enemigo
    spriteSheet.load(":/Imagenes/SpriteEnemigoAD.png");
    QPixmap spriteEnem2 = spriteSheet.copy(96, 0, 96, 96); // Sprite inicial del enemigo
    setPixmap(spriteEnem2);

    moveBy(500, 300);

    // Inicializar el temporizador para verificar la distancia con el jugador
    timerVerificarDistancia = new QTimer(this);
    connect(timerVerificarDistancia, &QTimer::timeout, this, &Enemigo2::actualizarPosicion);
    timerVerificarDistancia->start(50); // Ajusta el intervalo según sea necesario
}

void Enemigo2::setJugador(Jugador* jug) {
    jugador = jug;
}

void Enemigo2::actualizarPosicion() {
    if (jugador) {
        QPointF posicionJugador = jugador->obtenerPosicion();
        QPointF posicionEnemigo = obtenerPosicion();

        // Calcular la distancia en valor absoluto en el eje x
        qreal distanciaX = qAbs(posicionJugador.x() - posicionEnemigo.x());

        // Si la distancia en x es menor o igual a 200, lanza el dardo
        if (distanciaX <= 200 && !dardoLanzado) {
            lanzarDardo(posicionJugador);
        }
    }
}

void Enemigo2::lanzarDardo(const QPointF& posicionJugador)
{
    dardoLanzado = true;

    // Reproducir la animación de lanzar el dardo
    contadorAnimacion = 0;
    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Enemigo2::actualizarAnimacionLanzar);
    timerAnimacion->start(100); // Cada 100 ms se actualizará la animación

    // Lanzar el dardo después de que la animación termine
    QTimer::singleShot(600, [this, posicionJugador]() {
        lanzarDardoReal(posicionJugador);
    });
}


void Enemigo2::actualizarAnimacionLanzar()
{
    // Actualizar sprite según el frame de la animación
    int spriteX = 96 + (contadorAnimacion * 96);
    int spriteY = 0;
    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, 96, 96);
    setPixmap(sprite);

    contadorAnimacion++;
    if (contadorAnimacion == 6) { // Hay 6 imágenes para la animación
        contadorAnimacion = 0;
        timerAnimacion->stop();
        delete timerAnimacion;
        timerAnimacion = nullptr;
    }
}

void Enemigo2::lanzarDardoReal(const QPointF& posicionJugador)
{
    // Crea un nuevo objeto QGraphicsPixmapItem para el dardo
    QPixmap spriteDardo = spriteSheet.copy(6, 96, 6, 6);
    dardo = new QGraphicsPixmapItem(spriteDardo);
    scene()->addItem(dardo);

    // Establece la posición inicial del dardo
    dardo->setPos(obtenerPosicion());

    // Calcula la dirección del dardo hacia el jugador
    QLineF lineaDardo(obtenerPosicion(), posicionJugador);
    qreal angulo = lineaDardo.angle();

    // Determina si el jugador está a la izquierda o a la derecha del enemigo
    bool jugadorALaIzquierda = posicionJugador.x() < obtenerPosicion().x();
    qDebug() << posicionJugador.x() << obtenerPosicion().x();
    qDebug() << jugadorALaIzquierda;
    // Crea un temporizador para mover el dardo
    QTimer* timerDardo = new QTimer(this);
    connect(timerDardo, &QTimer::timeout, [=]() {
        // Mueve el dardo en la dirección calculada con una velocidad constante
        qreal dx = qCos(qDegreesToRadians(angulo)) * 10;
        qreal dy = qSin(qDegreesToRadians(angulo)) * 10;

        // Invierte el movimiento horizontal si el jugador está a la izquierda
        if (jugadorALaIzquierda) {
            dx = dx * (-1);
            qDebug() << dx;

        }
        //qDebug() << dx;
        dardo->moveBy(dx, dy);

        // Verifica si el dardo ha recorrido 200 unidades de distancia
        if (QLineF(obtenerPosicion(), dardo->pos()).length() >= 200) {
            scene()->removeItem(dardo);
            delete dardo;
            dardo = nullptr;
            dardoLanzado = false;
            timerDardo->stop();
            delete timerDardo;
        }
    });

    timerDardo->start(50); // Inicia el temporizador para mover el dardo cada 50 ms
}

QPointF Enemigo2::obtenerPosicion() const {
    return pos();
}
