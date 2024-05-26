#ifndef PARTICULA_H
#define PARTICULA_H

#include <QGraphicsItem>

class QTimer;

class Particula : public QGraphicsItem {
public:
    Particula(QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    // Reimplementación del evento Keypress
    void keyPressEvent(QKeyEvent *event) override;

    // Movimiento
    void moveBy(int dx, int dy);
    void on_pushButton_clicked();

private:
    qreal posX;
    qreal posY;
    QTimer *timer;

private slots:
    void movimiento();
};

#endif // PARTICULA_H
