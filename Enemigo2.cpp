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

void Enemigo2::setJugador(Jugador* jugador) {
    jugadorObj = jugador;
}

void Enemigo2::actualizarPosicion() {
    if (jugadorObj) {
        QPointF posicionJugador = jugadorObj->obtenerPosicion();
        QPointF posicionEnemigo = obtenerPosicion();

        // Calcular la distancia en valor absoluto en el eje x
        qreal distanciaX = qAbs(posicionJugador.x() - posicionEnemigo.x());

        // Determinar la dirección del dardo
        dardoHaciaLaDerecha = posicionJugador.x() > posicionEnemigo.x();

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
    dardoHaciaLaDerecha = posicionJugador.x() < obtenerPosicion().x();
    // Crea un nuevo objeto QGraphicsPixmapItem para el dardo
    QPixmap spriteDardo;
    if (dardoHaciaLaDerecha) {
        spriteDardo = spriteSheet.copy(6, 96, 6, 6);
    } else {
        // Reflejar el sprite del dardo horizontalmente
        spriteDardo = spriteSheet.copy(6, 96, 6, 6).transformed(QTransform().scale(-1, 1));
    }
    dardo = new QGraphicsPixmapItem(spriteDardo);
    scene()->addItem(dardo);

    // Establece la posición inicial del dardo
    QPointF posicionInicial = obtenerPosicion();
    dardo->setPos(posicionInicial);

    // Calcula el ángulo de rotación del dardo
    QPointF posicionEnemigo = obtenerPosicion();
    QLineF linea(posicionEnemigo, posicionJugador);
    qreal angulo = linea.angle();

    // Rota el sprite del dardo según el ángulo calculado
    rotarSpriteDardo(angulo);

    // Crea un temporizador para mover el dardo
    QTimer* timerDardo = new QTimer(this);
     // Inicia el temporizador para mover el dardo cada 50 ms
    connect(timerDardo, &QTimer::timeout, [=]() {
        // Mueve el dardo en la dirección calculada con una velocidad constante
        qreal dx = (dardoHaciaLaDerecha ? 10 : -10);
        dardo->moveBy(dx, 0); // Movimiento horizontal solamente

        // Verifica si el dardo ha recorrido 200 unidades de distancia o ha colisionado con el Jugador
        if (qAbs(dardo->pos().x() - posicionInicial.x()) >= 200 || dardo->collidesWithItem(jugadorObj)) {
            if (!vidaReducida) {
                qDebug() << "entro";
                jugadorObj->disminuirVida(2); // Restar 2 de vida al Jugador
                vidaReducida = true; // Establecer la bandera a true después de reducir la vida
            }
            scene()->removeItem(dardo);
            delete dardo;
            dardo = nullptr;
            dardoLanzado = false;
            timerDardo->stop();
            delete timerDardo;
            vidaReducida = false; // Restablecer la bandera para el próximo encuentro
        }
    });
    timerDardo->start(50);
}

void Enemigo2::rotarSpriteDardo(qreal angulo)
{
    // Crea un nuevo QGraphicsPixmapItem para el dardo rotado
    QPixmap spriteDardoRotado = spriteSheet.copy(6, 96, 6, 6);
    QTransform transform;
    if (dardoHaciaLaDerecha) {
        transform.rotate(-angulo);
    } else {
        transform.rotate(180 - angulo);
    }
    spriteDardoRotado = spriteDardoRotado.transformed(transform);

    // Actualiza el sprite del dardo con la imagen rotada
    dardo->setPixmap(spriteDardoRotado);
}

QPointF Enemigo2::obtenerPosicion() const {
    return pos();
}

void Enemigo2::verificarColisionJugador() {
    if (collidesWithItem(jugador)) {
        emit eliminarEnemigo();
    }
}


