#ifndef JUGADOR_H
#define JUGADOR_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>

class Jugador:public QObject,
                public QGraphicsPixmapItem //hereda de QObject (para características de objetos de Qt) y de QGraphicsPixmapItem (para objetos gráficos en una escena gráfica de Qt).
{
    Q_OBJECT
private:
    qreal x = 200;
    qreal y = 200;
    QSize viewRect;
    bool flag = true;
    int cont = 0;
    int spriteX = 0;
    int spriteY = 128;
    int spriteWidth = 0;
    int spriteHeight = 128;
    int contAdelante = 0;
    int contAtras = 0;
    bool movimientoHaciaAdelante = true;

    //salto
    bool enElAire = false; // Nueva bandera para controlar el estado de salto
    int alturaSalto = 100;  // Altura del salto ******
    QTimer* timerSalto = nullptr; // Temporizador para controlar el salto
    int contSalto = 0;
    bool enSalto;
    int alturaSaltoInicial; // Altura inicial del salto
    double velocidadInicial; // Velocidad inicial del salto
    double movimientoHorizontal; // Dirección del movimiento horizontal durante el salto
    double velocidadHorizontal; // Velocidad horizontal durante el salto


    QPixmap sprite;
    QPixmap spriteSheet;

    // Golpe
    bool golpeando = false; // Nueva bandera para controlar el estado de golpe
    int contGolpe = 0;
    QTimer* timerGolpe = nullptr; // Temporizador para la animación del golpe

private slots:



public:
    Jugador(QGraphicsView *view,QGraphicsItem* im = 0); //se inicializa con nullptr en el constructor. Valor predeterminado que se asigna al parámetro en caso de que no se proporcione ningún valor al crear un objeto de la clase.
    void keyPressEvent(QKeyEvent *event) override;
    // Movimiento
    void moveBy(int dx, int dy);
    //Simular caminar
    void setSprite(bool movimientoHaciaAdelante);

    void verificarColisiones();

    //salto
    void actualizarSalto();

    //golpe
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override; // Añadir la función para manejar el evento de clic del ratón
    void actualizarGolpe();
};

#endif // JUGADOR_H
