#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Particula.h"
#include "jugador.h"
#include "Enemigo1.h"
#include <qdebug.h>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) //La interfaz diseñada en Qt Designer
{
    ui->setupUi(this); //This hace referencia a la clase MainWindow, configura la interfaz de usuario definida en el Qt designer

    QGraphicsScene *scene = new QGraphicsScene(this); // se debe crear una escena para manejar elementos gráficos
    scene->setSceneRect(0, 0, 800, 800);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(800 + 2 * ui->graphicsView->frameWidth(), 800 + 2 * ui->graphicsView->frameWidth());//manejar la relación de aspecto

    QPixmap backgroundImage(":/Imagenes/background.jpg");
    QGraphicsPixmapItem *background = scene->addPixmap(backgroundImage);

    //PERSONAJES AÑADIR
    Enemigo1* enemigo = new Enemigo1(ui->graphicsView);
    scene->addItem(enemigo);
    enemigo->setPos(600, 200);

    Jugador *jug1 = new Jugador(ui->graphicsView);
    scene -> addItem(jug1);
    jug1->setPos(200,200);
    jug1->setFlag(QGraphicsItem::ItemIsFocusable);
    jug1->setFocus();
    //qDebug() << ui->graphicsView->size()<<" "<<scene->sceneRect();

    // Crea un cuadrado
    QGraphicsRectItem* cuadrado = new QGraphicsRectItem(0, 0, 50, 50);
    cuadrado->setBrush(Qt::red);
    scene->addItem(cuadrado);
    cuadrado->setPos(400, 200);

    // Crea un temporizador para verificar colisiones
    QTimer* timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, jug1, &Jugador::verificarColisiones);
    timerColisiones->start(16); // Verifica colisiones cada 16


}

MainWindow::~MainWindow()
{
    delete ui;
}
