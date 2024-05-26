#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Particula.h"
#include "jugador.h"
#include <qdebug.h>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) //La interfaz diseñada en Qt Designer
{
    ui->setupUi(this); //This hace referencia a la clase MainWindow, configura la interfaz de usuario definida en el Qt designer
    //bool clic = true; //No hay necesidad de declararla de nuevo
    QGraphicsScene *scene = new QGraphicsScene(this); // se debe crear una escena para manejar elementos gráficos
    scene->setSceneRect(0, 0, 800, 800);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(800 + 2 * ui->graphicsView->frameWidth(), 800 + 2 * ui->graphicsView->frameWidth());//manejar la relación de aspecto

    QPixmap backgroundImage(":/Imagenes/background.jpg");
    QGraphicsPixmapItem *background = scene->addPixmap(backgroundImage);


    QTimer *bgTimer = new QTimer(this);
    connect(bgTimer, &QTimer::timeout, [=]() {

        QPointF newPos = background->pos() - QPointF(1, 0); // Se ajustan las coordenadas del bg
        background->setPos(newPos);
        //qDebug() << newPos << " " << scene->width() << background->pos().x() + background->pixmap().width();


        if (background->pos().x() + background->pixmap().width() <= scene->width())
            background->setPos(QPointF(0, 0)); // Volver al principio de la imagen
    });
    bgTimer->start(50);


    Particula *bola = new Particula();
    scene->addItem(bola);

    Jugador *jug1 = new Jugador(ui->graphicsView);
    scene -> addItem(jug1);
    jug1->setPos(200,200);
    jug1->setFlag(QGraphicsItem::ItemIsFocusable);
    jug1->setFocus();
    //qDebug() << ui->graphicsView->size()<<" "<<scene->sceneRect();


    timer = new QTimer;
    //connect(timer,SIGNAL(timeout()),this,SLOT(hmov(*bola)));
    connect(timer, &QTimer::timeout, [=]() {
        hmov(bola);
    });
    timer->stop();

    // Crea un cuadrado
    QGraphicsRectItem* cuadrado = new QGraphicsRectItem(0, 0, 50, 50);
    cuadrado->setBrush(Qt::red);
    scene->addItem(cuadrado);
    cuadrado->setPos(400, 200);

    // Crea un temporizador para verificar colisiones
    QTimer* timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, jug1, &Jugador::verificarColisiones);
    timerColisiones->start(16); // Verifica colisiones cada 16

    // Crea un temporizador para verificar colisiones

    //connect(timerColisiones, &QTimer::timeout, jug1, &Jugador::verificarColisionesDer);
    //timerColisiones->start(16); // Verifica colisiones

    /*La función connect debe ser ajustada para conectar a la señal con el slot. La función hmov toma un puntero al objeto Particula como argumento
     * y no se puede conectar directamente al timeout del timer. Se puede utilizar una función lambda o una función auxiliar:
     *
     * private slots:
    void onTimeout(); // Declaration of the helper function

private:
    void connectTimer(); // Se crea una función para conectar el timer en el .h

Dentro del mainwindow.cpp:


void MainWindow::onTimeout() {
    hmov(bola);
}
Se define la función:
void MainWindow::connectTimer() {
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimeout);

La función "helper" o auxiliar no acepta parámetros sino que simplemente llama al slot hmov. Luego, hay una función connectTimer que es responsable de conectar la
señal de timeout.

     */




}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    if (clic){
       // ui->pushButton->setText("Hizo click");
        clic = false;
    }
    else{
        //ui->pushButton->setText("Haga clic");
        clic = true;
    }
    if (timer->isActive()) timer->stop();
    else timer->start(100);

}

void MainWindow::hmov(Particula *bola)
{
    bola->moveBy(5,0);
}
