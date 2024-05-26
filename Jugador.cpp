#include "Jugador.h"
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

//Definir el jugador y la imgen
Jugador::Jugador(QGraphicsView *view,QGraphicsItem *im):QGraphicsPixmapItem(im)
{
    setFlag(QGraphicsItem::ItemIsFocusable); // Mantener foco para eventos del teclado
    setFocus();
    //setPixmap(QPixmap(":/sprites.png"));
    x=200;
    y = 200;
    setFlag(QGraphicsItem::ItemIsFocusable); //Inicialización opcional para decir que tiene el foco para eventos del teclado
    //sceneRect = scene->sceneRect();
    //qDebug() << scene->sceneRect();
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
}


void Jugador::verificarColisiones()
{
    QList<QGraphicsItem*> colisionesItems = collidingItems();

    for (QGraphicsItem* item : colisionesItems) {
        // Verifica si el objeto es un cuadrado
        if (item->type() == QGraphicsRectItem::Type) {
            // Detiene el movimiento del jugador

            QPointF posicionObjetoColision = item->pos();

            int dx = posicionObjetoColision.x();
            //int dy = y - posicionObjetoColision.y();

            //qDebug() << dx << x;
            if (dx-128 < x && x < dx-10) {
                x -= 10;//izq
                movimientoHaciaAdelante = false;
                setSprite(movimientoHaciaAdelante);
                moveBy(0, 0);
            }
            else if ((dx+120) > x) {
                qDebug() << dx << x;
                x += 10;//der
                movimientoHaciaAdelante = true;
                setSprite(movimientoHaciaAdelante);
                moveBy(0, 0);

            }

            break;
        }
    }
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
        if (!enElAire) {
            enElAire = true;
            dy = -alturaSalto;
            timerSalto->start(350); // Iniciar el temporizador de salto
        }
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

void Jugador::moveBy(int dx, int dy)
{
    x += dx;
    y += dy;
    //qDebug() << x << " "<<y;
    //qDebug() << "Tecla: " << x << " " <<sceneRect.right()<<" "<<sceneRect.left();
    if (x>viewRect.width()-50||x<0){
        x-=dx;
    }
    setPos(x, y);

}

void Jugador::setSprite(bool movimientoHaciaAdelante)
{
    int spriteAncho, spriteAlto, spriteX, spriteY;

    if (golpeando) { // Si el jugador está golpeando
        spriteAncho = 128;
        spriteAlto = 128;
        spriteX = 128;
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
        sprite = spriteSheet.copy(spriteX * contGolpe, spriteY, spriteAncho, spriteAlto);
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
    double tiempo = contSalto * 70; // Ajusta el factor de tiempo según el intervalo del temporizador (220ms)
    double gravedad = 4; // Ajusta la gravedad según el efecto deseado

    // Calcular la posición vertical usando la fórmula del movimiento parabólico
    y = alturaSaltoInicial - (velocidadInicial * tiempo) + (0.5 * gravedad * tiempo * tiempo);

    // Verificar si el jugador ha alcanzado la posición inicial del salto
    if (y >= y) {
        // Aterriza cuando llega al suelo
        y = 200;
        enElAire = false;
        timerSalto->stop();
        contSalto = 0; // Reinicia el contador de salto para el próximo salto
    }

    // Actualizar la posición horizontal
    x += movimientoHorizontal * velocidadHorizontal;

    // Actualizar el sprite del jugador
    setSprite(movimientoHaciaAdelante);

    // Actualizar la posición del jugador
    setPos(x, y);
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
    setFocus(); // Volver a establecer el foco después de procesar el evento de clic
}



void Jugador::actualizarGolpe() {
    if (golpeando) {
        setSprite(golpeando); // Actualiza el sprite para la siguiente imagen de golpe
    }
}
