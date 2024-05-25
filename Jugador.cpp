#include "Jugador.h"
#include <QGraphicsScene>
#include <QLabel>
#include <QPixmap>
#include <QKeyEvent>
#include <QDebug>

//Definir el jugador y la imgen
Jugador::Jugador(QGraphicsView *view,QGraphicsItem *im):QGraphicsPixmapItem(im)
{
    //setPixmap(QPixmap(":/sprites.png"));
    x=200;
    y=200;
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
    int dx = 0, dy = 0; // Inicializa los desplazamientos en x e y


    //if (!puedeMoverse) {
    // El jugador no puede moverse, ignora el evento de tecla
    //return;
    //}

    switch (event->key()) {
    case Qt::Key_A:
        dx = -5; // Izquierda
        movimientoHaciaAdelante = false; // Establece y en
        break;
    case Qt::Key_D:
        dx = 5; // Derecha
        movimientoHaciaAdelante = true; // Tamaño en y sprite 144
        break;
    case Qt::Key_W:
        dy = -5; // Arriba
        break;
    case Qt::Key_S:
        dy = 5; // Abajo
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
        break;
    }

    // Verifica si se presionan las teclas W o S en combinación con A o D
    if (event->modifiers() & Qt::ShiftModifier) {
        // Se presionó la tecla Shift junto con otra tecla
        if (dx != 0 && dy != 0) {
            // Movimiento diagonal
            dx /= sqrt(2); // Ajusta la velocidad diagonal
            dy /= sqrt(2); // Ajusta la velocidad diagonal
        }
    }

    // Mueve el sprite en función de los desplazamientos dx y dy
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

    QPixmap sprite;
    if (movimientoHaciaAdelante) {
        sprite = spriteSheet.copy(spriteX * contAdelante, spriteY, spriteAncho, spriteAlto);
        contAdelante++;
        if (contAdelante == 8) {
            contAdelante = 0;
        }
    } else {
        sprite = spriteSheet.copy(spriteX * contAtras, spriteY, spriteAncho, spriteAlto);
        contAtras++;
        if (contAtras == 9) {
            contAtras = 0;
        }
    }

    setPixmap(sprite);
}
