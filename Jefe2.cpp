#include "Jefe2.h"

Jefe2::Jefe2(QGraphicsView* view, QGraphicsItem* im)
    : Enemigo2(view, im)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    spriteSheet.load(":/Imagenes/SpriteJefeB.png");
    QPixmap spriteJefe2 = spriteSheet.copy(0, 128, 128, 128);
    setPixmap(spriteJefe2);

    // Inicializar el temporizador para verificar la distancia con el jugador
    timerVerificarDistancia = new QTimer(this);
    connect(timerVerificarDistancia, &QTimer::timeout, this, &Jefe2::actualizarPosicion);
    timerVerificarDistancia->start(50);

    // Inicializar el temporizador para la animación de lanzamiento de flecha
    timerAnimacionFlecha = new QTimer(this);
    connect(timerAnimacionFlecha, &QTimer::timeout, this, &Jefe2::actualizarAnimacionLanzarFlecha);

    // Inicializar el temporizador para la animación de golpe
    timerAnimacionGolpe = new QTimer(this);
    connect(timerAnimacionGolpe, &QTimer::timeout, this, &Jefe2::actualizarAnimacionGolpe);

}

void Jefe2::actualizarPosicion()
{
    if (jugadorObj) {
        QPointF posicionJugador = jugadorObj->obtenerPosicion();
        QPointF posicionEnemigo = obtenerPosicion();

        qreal distanciaX = qAbs(posicionJugador.x() - posicionEnemigo.x());
        qreal distanciaY = qAbs(posicionJugador.y() - posicionEnemigo.y());

        flechaHaciaLaDerecha = posicionJugador.x() > posicionEnemigo.x();

        // Verificar si ha transcurrido suficiente tiempo desde el último golpe
        int tiempoTranscurrido = tiempoUltimoGolpe.msecsTo(QTime::currentTime());
        if (tiempoTranscurrido >= 2000) { // Ajusta el tiempo (en milisegundos) según tus necesidades
            puedeDisparar = true;
        }

        if (puedeDisparar) {
            if (distanciaX <= 300 && (distanciaY >= 0 && distanciaY <= 20) && !flechaLanzada) {
                //qDebug() << "entro";
                lanzarFlecha(posicionJugador);
            }
        }

        if (distanciaX <= 10 && !golpeando) {
            golpearJugador();
        }
    }
}

void Jefe2::lanzarFlecha(const QPointF& posicionJugador)
{
    flechaLanzada = true;

    contadorAnimacionFlecha = 0;
    timerAnimacionFlecha->start(50);

    QTimer::singleShot(1400, [this, posicionJugador]() {
        lanzarFlechaReal(posicionJugador);
    });
}

void Jefe2::setAnimacionLanzamientoFlechaSprite()
{
    int spriteAncho = 128;
    int spriteAlto = 128;
    int spriteY = 0;

    QPixmap spriteJefe2 = spriteSheet.copy(contadorAnimacionFlecha * spriteAncho, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteJefe2);
}

void Jefe2::actualizarAnimacionLanzarFlecha()
{
    contadorAnimacionFlecha++;
    if (contadorAnimacionFlecha == 14) {
        contadorAnimacionFlecha = 0;
        timerAnimacionFlecha->stop();
    }
    setAnimacionLanzamientoFlechaSprite();
}

void Jefe2::lanzarFlechaReal(const QPointF& posicionJugador)
{
    flechaHaciaLaDerecha = posicionJugador.x() < obtenerPosicion().x();

    QPolygonF polygonFlecha;
    if (flechaHaciaLaDerecha) {
        polygonFlecha << QPointF(0, 0) << QPointF(10, 5) << QPointF(10, -5);
    } else {
        polygonFlecha << QPointF(0, 0) << QPointF(-10, 5) << QPointF(-10, -5);
    }

    QPointF posicionEnemigo = obtenerPosicion();
    QLineF linea(posicionEnemigo, posicionJugador);
    qreal angulo = linea.angle();

    QTransform transformacion;
    transformacion.rotate(-angulo);
    polygonFlecha = transformacion.map(polygonFlecha);

    flecha = new QGraphicsPolygonItem(polygonFlecha);
    flecha->setBrush(Qt::red);
    scene()->addItem(flecha);

    QPointF posicionInicial = obtenerPosicion() + QPointF(pixmap().width() / 2, pixmap().height() / 2);
    flecha->setPos(posicionInicial);

    QTimer* timerFlecha = new QTimer(this);
    connect(timerFlecha, &QTimer::timeout, [=]() {
        qreal dx = (flechaHaciaLaDerecha ? 10 : -10);
        flecha->moveBy(dx, 0);

        if (qAbs(flecha->pos().x() - posicionInicial.x()) >= 300 || flecha->collidesWithItem(jugadorObj)) {
            if (!vidaReducida) {
                jugadorObj->disminuirVida(2);
                vidaReducida = true;
            }
            scene()->removeItem(flecha);
            delete flecha;
            flecha = nullptr;
            flechaLanzada = false;
            timerFlecha->stop();
            delete timerFlecha;
            vidaReducida = false;
        }
    });
    timerFlecha->start(50);
}

void Jefe2::golpearJugador()
{
    golpeando = true;
    contadorAnimacionGolpe = 0;
    timerAnimacionGolpe->start(100);
}

void Jefe2::setGolpeandoSprite()
{
    int spriteAncho = 128;
    int spriteAlto = 128;
    int spriteY = 128;

    QPixmap spriteJefe2 = spriteSheet.copy(contadorAnimacionGolpe * spriteAncho, spriteY, spriteAncho, spriteAlto);
    setPixmap(spriteJefe2);
}

void Jefe2::actualizarAnimacionGolpe()
{
    contadorAnimacionGolpe++;
    if (contadorAnimacionGolpe == 5) {
        contadorAnimacionGolpe = 0;
        golpeando = false;
        timerAnimacionGolpe->stop();
        jugadorObj->disminuirVida(5);

        // Guardar el tiempo del último golpe y deshabilitar temporalmente el lanzamiento de flechas
        tiempoUltimoGolpe = QTime::currentTime();
        puedeDisparar = false;
    }
    setGolpeandoSprite();
}

void Jefe2::setJugador(Jugador* jugador) {
    jugadorObj = jugador;
}

QPointF Jefe2::obtenerPosicion() const {
    return pos();
}
