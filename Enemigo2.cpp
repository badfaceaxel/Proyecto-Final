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
    //Timer golpe lanzamiento
    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Enemigo2::actualizarAnimacionLanzar);

}

void Enemigo2::setJugador(Jugador* jugador) {
    jugadorObj = jugador;
}

void Enemigo2::actualizarPosicion() {
    if (jugadorObj) {
        QPointF posicionJugador = jugadorObj->obtenerPosicion();
        QPointF posicionEnemigo = obtenerPosicion();

        // Calcular la distancia en valor absoluto en el eje x e y
        qreal distanciaX = qAbs(posicionJugador.x() - posicionEnemigo.x());
        qreal distanciaY = qAbs(posicionJugador.y() - posicionEnemigo.y());
        //qDebug() << posicionJugador.y() << posicionEnemigo.y();
        //qDebug() << distanciaX << distanciaY;
        // Determinar la dirección del dardo
        dardoHaciaLaDerecha = posicionJugador.x() > posicionEnemigo.x();

        // Si la distancia en x es menor o igual a 200 y la distancia en y es menor o igual a 20, lanza el dardo
        if (distanciaX <= 200 && (distanciaY >= 25 && distanciaY <= 33) && !dardoLanzado) {
            lanzarDardo(posicionJugador);
        }
    }
}

void Enemigo2::lanzarDardo(const QPointF& posicionJugador)
{
    dardoLanzado = true;

    // Reproducir la animación de lanzar el dardo
    contadorAnimacion = 0;
    timerAnimacion->start(100); // Cada 100 ms se actualizará la animación

    // Lanzar el dardo después de que la animación termine
    QTimer::singleShot(600, [this, posicionJugador]() {
        lanzarDardoReal(posicionJugador);
    });
}


void Enemigo2::setAnimacionLanzamientoSprite() {
    int spriteAncho = 96;
    int spriteAlto = 96;
    int spriteY = 0;

    QPixmap sprite = spriteSheet.copy(contadorAnimacion * spriteAncho, spriteY, spriteAncho, spriteAlto);
    setPixmap(sprite);
}

void Enemigo2::actualizarAnimacionLanzar() {


    contadorAnimacion++;
    if (contadorAnimacion == 6) { // Hay 6 imágenes para la animación
        contadorAnimacion = 0;
        timerAnimacion->stop();

    }
    setAnimacionLanzamientoSprite();
}

void Enemigo2::lanzarDardoReal(const QPointF& posicionJugador)
{
    dardoHaciaLaDerecha = posicionJugador.x() < obtenerPosicion().x();

    // Crea un nuevo QGraphicsPolygonItem para el dardo (triángulo)
    QPolygonF polygonDardo;
    if (dardoHaciaLaDerecha) {
        polygonDardo << QPointF(0, 0) << QPointF(10, 5) << QPointF(10, -5);
    } else {
        polygonDardo << QPointF(0, 0) << QPointF(-10, 5) << QPointF(-10, -5);
    }

    // Calcular el ángulo de rotación del dardo
    QPointF posicionEnemigo = obtenerPosicion();
    QLineF linea(posicionEnemigo, posicionJugador);
    qreal angulo = linea.angle();

    // Rotar los puntos del polígono
    QTransform transformacion;
    transformacion.rotate(-angulo);
    polygonDardo = transformacion.map(polygonDardo);

    dardo = new QGraphicsPolygonItem(polygonDardo);
    dardo->setBrush(Qt::red); // Establece el color del triángulo
    scene()->addItem(dardo);

    // Establece la posición inicial del dardo
    QPointF posicionInicial = obtenerPosicion() + QPointF(pixmap().width() / 2, pixmap().height() / 2);
    dardo->setPos(posicionInicial);

    // Crea un temporizador para mover el dardo
    QTimer* timerDardo = new QTimer(this);
    connect(timerDardo, &QTimer::timeout, [=]() {
        // Mueve el dardo en la dirección calculada con una velocidad constante
        qreal dx = (dardoHaciaLaDerecha ? 10 : -10);
        dardo->moveBy(dx, 0); // Movimiento horizontal solamente

        // Verifica si el dardo ha recorrido 200 unidades de distancia o ha colisionado con el Jugador
        if (qAbs(dardo->pos().x() - posicionInicial.x()) >= 200 || dardo->collidesWithItem(jugadorObj)) {
            if (!vidaReducida) {
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

QPointF Enemigo2::obtenerPosicion() const {
    return pos();
}

void Enemigo2::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug() << "Hola";

}

bool Enemigo2::eventFilter(QObject *obj, QEvent *event) {
    //qDebug() << "2.0HOLA";
    return false;

}

void Enemigo2::actualizarCaida() {
    //qDebug() << "3.0 Hola";
}
