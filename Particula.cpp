#include "Particula.h"
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QObject>

Particula::Particula(QGraphicsItem *parent) : QGraphicsItem(parent), posX(0), posY(0) {
    setFlag(QGraphicsItem::ItemIsFocusable);
}

QRectF Particula::boundingRect() const {
    return QRectF(-5, -5, 10, 10);
}

void Particula::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setBrush(Qt::red);
    painter->drawEllipse(-5, -5, 10, 10);
}

void Particula::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
    case Qt::Key_Up:
        moveBy(0, -5);
        break;
    case Qt::Key_Down:
        moveBy(0, 5);
        break;
    case Qt::Key_A:
        moveBy(-5, 0);
        break;
    case Qt::Key_D:
        moveBy(5, 0);
        break;
    case Qt::Key_W:
        moveBy(0, -5);
        break;
    case Qt::Key_S:
        moveBy(0, 5);
        break;
    default:
        QGraphicsItem::keyPressEvent(event);
    }
}

void Particula::moveBy(int dx, int dy) {
    posX += dx;
    posY += dy;
    setPos(posX, posY);
}

void Particula::movimiento() {
    static int direction = 1;
    posY += direction * 5;
    setPos(posX, posY);

    if (posY <= -100 || posY >= 100) {
        direction *= -1;
    }
}
