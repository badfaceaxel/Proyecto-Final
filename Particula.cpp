#include "Particula.h"
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>

Particula::Particula(QGraphicsItem *parent) : QGraphicsItem(parent), posX(0), posY(0)
{
    setFlag(QGraphicsItem::ItemIsFocusable); //Inicialización opcional para decir que tiene el foco para eventos del teclado

}

QRectF Particula::boundingRect() const
{
    return QRectF(-5, -5, 10, 10); // Xoordenadas iniciales del rect (sobre el origen del punto), unidades a la derecha y unidades abajo
}

void Particula::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(-5, -5, 10, 10); // Adjust as needed
}


void Particula::moveBy(int dx, int dy)
{
    posX += dx;
    posY += dy;
    setPos(posX, posY);
}

void Particula::movimiento()
{
    static int direction = 1;
    posY += direction * 5;
    setPos(posX, posY);


    if (posY <= -100 || posY >= 100) {
        direction *= -1;
    }
}
