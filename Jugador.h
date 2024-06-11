#ifndef JUGADOR_H
#define JUGADOR_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>
#include <QFile>      //txt
#include <QTextStream>

class Level1;

class Jugador:public QObject, public QGraphicsPixmapItem //hereda de QObject (para características de objetos de Qt) y de QGraphicsPixmapItem (para objetos gráficos en una escena gráfica de Qt).
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
    bool enElAire = false; // Bandera para controlar si el jugador está saltando
    //QTimer* timerSalto = nullptr; // Temporizador para controlar el salto
    int alturaSalto = 100; // Altura del salto
    int alturaSaltoInicial; // Altura inicial del salto
    double velocidadInicial; // Velocidad inicial del salto
    double movimientoH; // Dirección del movimiento horizontal durante el salto
    double velocidadHorizontal; // Velocidad horizontal durante el salto
    int contSalto = 0; // Contador para controlar el salto
    QPointF posicionInicial; // Posición inicial antes del salto
    bool colisionEnElAire = false; // Velocidad horizontal durante el salto
    int alturaSaltoSinColision = 350;

    // Golpe
    bool golpeando = false; // Nueva bandera para controlar el estado de golpe
    int contGolpe = 0;
    QTimer* timerGolpe = nullptr; // Temporizador para la animación del golpe

    //VIDAAAAAAAAAA
    int vida = 100;

    //instancias
    bool posicionInicialEstablecida = true;

    //Cambios Axel

    int limiteIzquierdo = 0;   //CambioEscena
    int limiteDerecho = 3200;  // Valor inicial que se actualizará
    QString nickname;  // NickName         //CambioAxel

    int puntuacion = 0; //
    QVector<QPair<QString, int>> registros; // Nuevo atributo para almacenar los registros



private slots:



public:
    Jugador(QGraphicsView *view, QGraphicsItem *im = 0); //se inicializa con nullptr en el constructor. Valor predeterminado que se asigna al parámetro en caso de que no se proporcione ningún valor al crear un objeto de la clase.
    void keyPressEvent(QKeyEvent *event) override;
    // Movimiento
    void moveBy(int dx, int dy);
    //Simular caminar
    void setSprite(bool movimientoHaciaAdelante);

    void verificarColisiones();
    void movimientoHorizontal(int desplazamiento);

    //salto
    void actualizarSalto();
    bool Colision = false;
    QTimer* timerSalto = nullptr;

    //golpe
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override; // Añadir la función para manejar el evento de clic del ratón
    void actualizarGolpe();
    bool eventFilter(QObject* obj, QEvent* event);

    //Reconocimiento
    QPointF obtenerPosicion() const;


    //Vida
    void disminuirVida(int cantidad);

    //Verificaciones
    QTimer* timerCaida = nullptr;
    virtual void actualizarCaida();
    double velocidadVertical = 0.0;
    double aceleracionGravedad = 0.3;

    //CambiosAxel

    void setNickname(const QString& name) { nickname = name; }   //CambioAxel
    QString getNickname() const { return nickname; }             //CambioAxel
    void setLimites(int izquierdo, int derecho);   //CambioEscena
    qreal getX() const { return x; }
    qreal getY() const { return y; }

    void guardarDatos();
    void cargarDatos();
    int getPuntuacion() const { return puntuacion; }
    void setPuntuacion(int nuevaPuntuacion) { puntuacion = nuevaPuntuacion; }
    const QVector<QPair<QString, int>>& getRegistros() const { return registros; }
    int getVida() const { return vida; }

    void aumentarPuntuacion(int puntos); //Puntuacion

protected:
    QPixmap sprite;
    QPixmap spriteSheet;

signals:

    //CAMBIOSaXEL

    void posicionCambiada();
    void vidaCambiada(int nuevaVida);
    void puntuacionCambiada(int nuevaPuntuacion);   //Puntuacion

    void vidaCero();

};

#endif // JUGADOR_H
