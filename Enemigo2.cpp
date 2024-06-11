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
    spriteSheet.load(":/Media/SpriteEnemigoAD.png");
    QPixmap spriteEnem2 = spriteSheet.copy(96, 0, 96, 96); // Sprite inicial del enemigo
    setPixmap(spriteEnem2);

    //moveBy(500, 300);

    // Inicializar el temporizador para verificar la distancia con el jugador
    timerVerificarDistancia = new QTimer(this);
    connect(timerVerificarDistancia, &QTimer::timeout, this, &Enemigo2::actualizarPosicion);
    timerVerificarDistancia->start(50); // Ajusta el intervalo según sea necesario
    //Timer golpe lanzamiento
    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Enemigo2::actualizarAnimacionLanzar);
    timerDardo = new QTimer(this);
    connect(timerDardo, &QTimer::timeout, this, &Enemigo2::moverDardo);
    timerRetraso = new QTimer(this);
    connect(timerRetraso, &QTimer::timeout, this, &Enemigo2::iniciarLanzamientoDardo);
}

void Enemigo2::setJugador(Jugador* jugador) {
    jugadorObj = jugador;
}

void Enemigo2::iniciarLanzamientoDardo()
{
    lanzarDardo(jugadorObj->obtenerPosicion());
    timerRetraso->stop(); // Detener el temporizador de retraso
}

void Enemigo2::actualizarPosicion()
{
    if (jugadorObj) {
        QPointF posicionJugador = jugadorObj->obtenerPosicion();
        QPointF posicionEnemigo = obtenerPosicion();

        // Calcular la distancia en valor absoluto en el eje x e y
        qreal distanciaX = qAbs(posicionJugador.x() - posicionEnemigo.x());
        qreal distanciaY = qAbs(posicionJugador.y() - posicionEnemigo.y());

        // Determinar la dirección del dardo
        dardoHaciaLaDerecha = posicionJugador.x() > posicionEnemigo.x();

        // Si la distancia en x es menor o igual a 200 y la distancia en y es menor o igual a 20
        if (distanciaX <= 200 && (distanciaY >= 10 && distanciaY < 60) && !dardoLanzado) {
            if (!jugadorEnRango) { // Si el jugador entra en el rango por primera vez
                jugadorEnRango = true; // Establecer la bandera a true
                timerRetraso->start(1300); // Iniciar el temporizador de retraso de 1.5 segundos
            }
        } else {
            jugadorEnRango = false; // Si el jugador sale del rango, restablecer la bandera
            timerRetraso->stop(); // Detener el temporizador de retraso
        }
    }
}

void Enemigo2::lanzarDardo(const QPointF& posicionJugador)
{
    dardoLanzado = false;

    // Eliminar el dardo existente si hay uno
    if (dardo != nullptr) {
        scene()->removeItem(dardo);
        delete dardo;
        dardo = nullptr;
        timerDardo->stop();
        delete timerDardo;
        timerDardo = nullptr;
    }

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

void Enemigo2::lanzarDardoReal(const QPointF& posicionJugadorParam)
{
    dardoHaciaLaDerecha = posicionJugadorParam.x() > obtenerPosicion().x();
    posicionJugador = posicionJugadorParam;
    posicionInicial = obtenerPosicion() + QPointF(pixmap().width() / 2, pixmap().height() / 2);

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
    dardo->setPos(posicionInicial);

    // Crea un nuevo temporizador para mover el dardo
    if (!timerDardo) {
        timerDardo = new QTimer(this);
        connect(timerDardo, &QTimer::timeout, this, &Enemigo2::moverDardo);
    }
    timerDardo->start(130);
    desaceleracionDardo = 10.0; // Velocidad inicial del dardo
}

void Enemigo2::moverDardo()
{
    if (dardo != nullptr) {
        // Mueve el dardo en la dirección calculada con desaceleración
        qreal dx = (dardoHaciaLaDerecha ? desaceleracionDardo : -desaceleracionDardo);
        dardo->moveBy(dx, 0); // Movimiento horizontal solamente

        // Reducir la desaceleración en cada iteración
        desaceleracionDardo *= 0.95; // Ajusta este valor para controlar la tasa de desaceleración

        // Verifica si el dardo ha recorrido 200 unidades de distancia
        if (qAbs(dardo->pos().x() - posicionInicial.x()) >= 200) {
            eliminarDardo();
        } else if (dardo->collidesWithItem(jugadorObj)) {
            // El dardo colisiona con el Jugador
            if (!vidaReducida) {
                jugadorObj->disminuirVida(2); // Restar 2 de vida al Jugador
                vidaReducida = true; // Establecer la bandera a true después de reducir la vida
            }
            eliminarDardo();
        }
    }
}

void Enemigo2::eliminarDardo()
{
    //qDebug() << "Entrando a eliminarDardo()";

    if (timerDardo != nullptr) {
        timerDardo->stop();
        delete timerDardo;
        timerDardo = nullptr;
    }

    if (timerRetraso != nullptr) {
        timerRetraso->stop();
    }

    vidaReducida = false;

    // Eliminar el dardo si aún existe
    if (dardo != nullptr) {
        //qDebug() << "Dardo no es nulo, preparando para eliminarlo";
        scene()->removeItem(dardo);
        delete dardo;
        dardo = nullptr;
        //qDebug() << "Dardo eliminado";
    } else {
        //qDebug() << "Dardo es nulo, no se eliminará";
    }

    dardoLanzado = false;
    //qDebug() << "Saliendo de eliminarDardo()";
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

