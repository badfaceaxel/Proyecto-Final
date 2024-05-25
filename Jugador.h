#ifndef JUGADOR_H
#define JUGADOR_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>

class Jugador:public QObject,
                public QGraphicsPixmapItem //hereda de QObject (para características de objetos de Qt) y de QGraphicsPixmapItem (para objetos gráficos en una escena gráfica de Qt).
{
    Q_OBJECT
private:
    qreal x=200;
    qreal y=200;
    QSize viewRect;
    bool flag=true;
    int cont=0;
    int spriteX = 0;
    int spriteY = 128;
    int spriteWidth = 0;
    int spriteHeight = 128;
    int contAdelante = 0;
    int contAtras = 0;
    bool movimientoHaciaAdelante = true;

    QPixmap sprite;
    QPixmap spriteSheet;

private slots:



public:
    Jugador(QGraphicsView *view,QGraphicsItem* im = 0); //se inicializa con nullptr en el constructor. Valor predeterminado que se asigna al parámetro en caso de que no se proporcione ningún valor al crear un objeto de la clase.
    void keyPressEvent(QKeyEvent *event) override;
    // Movimiento
    void moveBy(int dx, int dy);
    //Simular caminar
    void setSprite(bool movimientoHaciaAdelante);

    void verificarColisiones();

};
#endif // JUGADOR_H
