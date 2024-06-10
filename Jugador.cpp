#include "Jugador.h"
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "Enemigo1.h"
#include "Enemigo2.h"


//Definir el jugador y la imgen
Jugador::Jugador(QGraphicsView *view, QGraphicsItem *im):QGraphicsPixmapItem(im)
{

    setFlag(QGraphicsItem::ItemIsFocusable); // Mantener foco para eventos del teclado
    setFocus();

    x=200;
    y = 200;
    setFlag(QGraphicsItem::ItemIsFocusable); //Inicialización opcional para decir que tiene el foco para eventos del teclado

    viewRect = view->size();
    QRectF sceneRect = view->sceneRect();
    //qDebug() << viewRect << " "<< sceneRect << " "<<view->size().width();
    spriteSheet.load(":/Imagenes/SpriteADE.png");

    QPixmap sprite = spriteSheet.copy(spriteX, spriteY, 128, spriteHeight);
    setPixmap(sprite);
    setSprite(true);

    timerSalto = new QTimer(this); // Inicializar el temporizador
    connect(timerSalto, &QTimer::timeout, this, &Jugador::actualizarSalto); // Conectar la señal timeout del temporizador a la función actualizarSalto


    setAcceptedMouseButtons(Qt::LeftButton); // Aceptar clics del botón izquierdo del ratón
    setFlag(QGraphicsItem::ItemIsFocusable); // Mantener foco para eventos del teclado
    setFocus(); // Establecer foco

    timerGolpe = new QTimer(this); // Inicializar el temporizador para el golpe
    connect(timerGolpe, &QTimer::timeout, this, &Jugador::actualizarGolpe); // Conectar la señal timeout del temporizador a la función actualizarGolpe
    view->setMouseTracking(true); // Habilitar el seguimiento del mouse en la vista
    view->viewport()->installEventFilter(this); // Instalar un filtro de eventos en el viewport

    timerCaida = new QTimer(this);
    connect(timerCaida, &QTimer::timeout, this, &Jugador::actualizarCaida);
    timerCaida->start(10);
}


void Jugador::verificarColisiones()
{
    /*QList<QGraphicsItem*> colisionesItems = collidingItems();

    for (QGraphicsItem* item : colisionesItems) {
        // Verifica si el objeto es un cuadrado
        if (item->type() == QGraphicsRectItem::Type) {
            // Detiene el movimiento del jugador

            QPointF posicionObjetoColision = item->pos();

            int dx = posicionObjetoColision.x();
            int dy = posicionObjetoColision.y();
            int objetoAncho = item->boundingRect().width();
            int objetoAlto = item->boundingRect().height();
            int jugadorAlto = boundingRect().height();
            qDebug() << dy << y << jugadorAlto;
            qDebug() << objetoAncho << objetoAlto;

            //qDebug() << dx << x;
            if (dx-128 < x && x < dx-10 && (y + jugadorAlto - 10 > dy && y < dy + objetoAlto) && dy > y+20 ) {
                x -= 10;//izq
                movimientoHaciaAdelante = false;
                setSprite(movimientoHaciaAdelante);
                moveBy(0, 0);
            }
            else if ((dx+120) > x && (y + jugadorAlto - 10 > dy && y < dy + objetoAlto) && dy > y+20) {
                qDebug() << dx << x;
                x += 10;//der
                movimientoHaciaAdelante = true;
                setSprite(movimientoHaciaAdelante);
                moveBy(0, 0);

            } else if ((dy-y-objetoAlto) < (y+objetoAlto) && dy > y+20 ) {
                // Colisión por encima del bloque
                qDebug() << dy;
                qDebug() << y;
                y -= 5;
                qDebug() << y;
                bool Colision = true;
                movimientoHaciaAdelante = false; // Detiene el movimiento hacia adelante
                setSprite(movimientoHaciaAdelante);
                moveBy(0, 0);
            } else if ((dy > y)){
                y += 5;
                setSprite(movimientoHaciaAdelante);

                moveBy(0, 0);
            }
            moveBy(0, 0);
            break;
        }
    }*/
}

void Jugador::keyPressEvent(QKeyEvent *event)
{
    int dx = 0, dy = 0;

    switch (event->key()) {
    case Qt::Key_A:
        if (enElAire) {
            dx = -100; // Salto hacia la izquierda ****
            movimientoHaciaAdelante = false;
        } else {
            dx = -5; // Movimiento normal hacia la izquierda
            movimientoHaciaAdelante = false;
        }
        break;
    case Qt::Key_D:
        if (enElAire) {
            dx = 100; // Salto hacia la derecha ****
            movimientoHaciaAdelante = true;
        } else {
            dx = 5; // Movimiento normal hacia la derecha
            movimientoHaciaAdelante = true;
        }
        break;
    case Qt::Key_W:
        if (!enElAire) { // Salta solo si el jugador no está en el aire
            dy = -alturaSalto; // Establece el valor inicial de dy para el salto
            alturaSaltoInicial = y;
            enElAire = true; // Establece la bandera enElAire como verdadera
            timerCaida->stop();
            timerSalto->start(450); // Inicia el temporizador de salto
        }
        break;
    case Qt::Key_Q:
        dy = -5;
        movimientoHaciaAdelante = false;
        break;
    case Qt::Key_S:
        dy = 5;
        movimientoHaciaAdelante = false;
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
        break;
    }

    if (event->modifiers() & Qt::ShiftModifier) {
        if (dx != 0 && dy != 0) {
            dx /= sqrt(2);
            dy /= sqrt(2);
        }
    }

    moveBy(dx, dy);
    setSprite(movimientoHaciaAdelante);
}

void Jugador::moveBy(int dx, int dy) {
    // Calcular nueva posición potencial
    qreal newX = x + dx;
    qreal newY = y + dy;

    // Verificar límites de posición
    if (newX < 0) {
        newX = 0;
    } else if (newX > 800) {
        newX = 0;
    }

    // Actualizar posición
    x = newX;
    y = newY;

    // Establecer nueva posición
    setPos(x, y);
}

void Jugador::setSprite(bool movimientoHaciaAdelante)
{
    int spriteAncho, spriteAlto, spriteX, spriteY;

    if (golpeando) { // Si el jugador está golpeando
        spriteAncho = 128;
        spriteAlto = 128;
        spriteX = 0;
        spriteY = 384;
    } else if (enElAire) { // Si el jugador está en el aire (saltando)
        spriteAncho = 144;
        spriteAlto = 128;
        spriteX = 128;
        spriteY = 256;
    } else { // Si el jugador está en el suelo
        if (movimientoHaciaAdelante) {
            spriteAncho = 128;
            spriteAlto = 128;
            spriteX = 128;
            spriteY = 0;
        } else {
            spriteAncho = 144;
            spriteAlto = 128;
            spriteX = 128;
            spriteY = 128;
        }
    }

    QPixmap sprite;
    if (golpeando) {
        sprite = spriteSheet.copy(spriteAncho * contGolpe, spriteY, spriteAncho, spriteAlto);
        contGolpe++;
        if (contGolpe == 5) { // Hay 5 imágenes para la animación de golpe
            contGolpe = 0;
            golpeando = false; // Termina la animación de golpe
            timerGolpe->stop(); // Detiene el temporizador
        }
    } else if (movimientoHaciaAdelante) {
        sprite = spriteSheet.copy(spriteX * contAdelante, spriteY, spriteAncho, spriteAlto);
        contAdelante++;
        if (contAdelante == 8) {
            contAdelante = 0;
        }
    } else if (!movimientoHaciaAdelante){
        sprite = spriteSheet.copy(spriteX * contAtras, spriteY, spriteAncho, spriteAlto);
        contAtras++;
        if (contAtras == 9) {
            contAtras = 0;
        }
    } else if (enElAire){
        sprite = spriteSheet.copy(spriteX * contAtras, spriteY, spriteAncho, spriteAlto);
        contSalto++;
        if (contSalto == 9) {
            contSalto = 0;
        }
    }

    setPixmap(sprite);
}

void Jugador::actualizarSalto()
{
    // Ajustar el tiempo y la gravedad para controlar la altura y la duración del salto
    double tiempo = timerSalto->interval() / 70.0; // Tiempo transcurrido en segundos
    double gravedad = 2; // Ajusta la gravedad según el efecto deseado

    // Calcular la posición vertical usando la fórmula del movimiento parabólico
    y += velocidadInicial * tiempo + 0.5 * gravedad * tiempo * tiempo;

    // Invertir la velocidad vertical cuando se alcance la altura máxima del salto
    if (y <= alturaSaltoInicial - alturaSalto) {
        velocidadInicial = -velocidadInicial;
    }

    // Verificar colisiones con objetos y ajustar la posición si es necesario
    QList<QGraphicsItem*> colisionesItems = collidingItems();
    for (QGraphicsItem* item : colisionesItems) {
        if (item->type() == QGraphicsRectItem::Type) {
            QPointF posicionObjetoColision = item->pos();
            int dy = posicionObjetoColision.y();
            int objetoAlto = item->boundingRect().height();

            if ((dy-y-objetoAlto) < (y+objetoAlto) && dy > y+20 ) {
                //qDebug() << "ENTROOOOOOOOO";
                // Colisión por encima del bloque
                y = dy - boundingRect().height() ; // Ajustar la posición vertical del jugador
                //qDebug() << y;
                velocidadInicial = 0; // Detener el movimiento vertical
                enElAire = false; // Establecer la bandera enElAire como falsa
                timerSalto->stop(); // Detener el temporizador de salto
                timerCaida->start(10);
                Colision = true;
                setSprite(movimientoHaciaAdelante);
                break;
            }
        }
    }

    // Actualizar la posición del jugador

    //x += movimientoH * velocidadHorizontal + 5;
    setPos(x, y);
    //qDebug() << alturaSaltoInicial;
    //qDebug() << y;
    if(y >= alturaSaltoInicial){
        enElAire = false;
    }
   //qDebug() << y;
        // Verificar si el jugador ha alcanzado la posición inicial del salto
    if (!enElAire && y >= alturaSaltoInicial && !Colision) {
        //qDebug() << "ENTROOOOOOOOO2";
        y = alturaSaltoInicial; // Restaurar la posición inicial
        timerSalto->stop();
        setSprite(movimientoHaciaAdelante);
        setPos(x, y);
    }

}

void Jugador::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton && !golpeando) {
        golpeando = true;
        contGolpe = 0; // Reinicia el contador de golpe
        timerGolpe->start(100); // Inicia el temporizador para la animación de golpe
        setSprite(golpeando); // Actualiza el sprite para la primera imagen de golpe
    } else {
        QGraphicsPixmapItem::mousePressEvent(event);
    }
    setFocus();
}



void Jugador::actualizarGolpe() {
    if (golpeando) {
        setSprite(golpeando); // Actualiza el sprite para la siguiente imagen de golpe
        setFocus();

        // Obtener una lista de todos los elementos con los que colisiona el jugador
        QList<QGraphicsItem*> colisionesItems = collidingItems();
        for (QGraphicsItem* item : colisionesItems) {
            // Verificar si el elemento es un Enemigo1
            Enemigo1* enemigo1 = dynamic_cast<Enemigo1*>(item);
            if (enemigo1) {
                enemigo1->setVisible(false); // Hacer al enemigo invisible antes de emitir la señal
                enemigo1->spriteSheet = QPixmap();
                emit enemigo1->eliminarEnemigo();
            }

            // Verificar si el elemento es un Enemigo2
            Enemigo2* enemigo2 = dynamic_cast<Enemigo2*>(item);
            if (enemigo2 != nullptr && !enemigo2->yaEliminado) {
                //qDebug() << "Colisión con Enemigo2 detectada";
                enemigo2->setVisible(false); // Hacer al enemigo invisible antes de emitir la señal
                enemigo2->spriteSheet = QPixmap();
                enemigo2->yaEliminado = true;
                emit enemigo2->eliminarEnemigo();

                // Crear copias locales de los miembros relevantes
                bool dardoExistente = (enemigo2->dardo != nullptr);
                QGraphicsScene* escena = scene();

                // Verificar si enemigo2 y el dardo existen antes de intentar eliminar el dardo
                if (dardoExistente) {
                    //qDebug() << "Eliminando dardo de Enemigo2";
                    escena->removeItem(enemigo2->dardo);
                    delete enemigo2->dardo;
                    enemigo2->dardo = nullptr;
                    //qDebug() << "Dardo eliminado";
                } else {
                    //qDebug() << "Dardo de Enemigo2 es nulo, no se eliminará";
                }

                // Salir del ciclo después de eliminar al Enemigo2
                break;
            }
        }
    }
}

bool Jugador::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton && !golpeando) {
            golpeando = true;
            contGolpe = 0; // Reinicia el contador de golpe
            timerGolpe->start(100); // Inicia el temporizador para la animación de golpe
            setSprite(golpeando); // Actualiza el sprite para la primera imagen de golpe
        }
    }
    setFocus();
    return false; // Devuelve false para permitir que otros componentes manejen el evento
}

QPointF Jugador::obtenerPosicion() const
{
    return QPointF(x, y);
}

void Jugador::disminuirVida(int cantidad) {
    vida -= cantidad;
    qDebug() << vida;
    if (vida <= 0) {
        // Aquí puedes agregar código para manejar cuando el jugador se queda sin vida
        //qDebug() << "El jugador ha perdido toda su vida";
    }
}

void Jugador::actualizarCaida()
{
    // Verificar colisiones con objetos y ajustar la posición si es necesario
    QList<QGraphicsItem*> colisionesItems = collidingItems();
    bool colisionSuelo = false;
    for (QGraphicsItem* item : colisionesItems) {
        if (item->type() == QGraphicsRectItem::Type) {
            QPointF posicionObjetoColision = item->pos();
            int dy = posicionObjetoColision.y();
            int objetoAlto = item->boundingRect().height();

            if (dy - y - objetoAlto <= boundingRect().height() && dy > y) {
                // Colisión con el suelo
                y = dy - boundingRect().height();
                velocidadVertical = 0;
                colisionSuelo = true;
                break;
            }
        }
    }

    if (!colisionSuelo) {
        velocidadVertical += aceleracionGravedad;
        y += velocidadVertical;
    }

    setPos(x, y);
}
