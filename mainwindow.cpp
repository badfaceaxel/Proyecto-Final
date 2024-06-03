#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Particula.h"
#include "jugador.h"
#include "Enemigo1.h"
#include "Enemigo2.h"
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

    Jugador *jug1 = new Jugador(ui->graphicsView);
    scene -> addItem(jug1);
    jug1->setPos(200,200);

    //qDebug() << ui->graphicsView->size()<<" "<<scene->sceneRect();

    //PERSONAJES AÑADIR

    // Crear enemigos
    enemies = Enemigo1::crearEnemigos(ui->graphicsView, jug1, scene);

    // Conectar la señal de eliminarEnemigo para cada instancia
    for (Enemigo1* enemigo : qAsConst(enemies)) {
        connect(enemigo, &Enemigo1::eliminarEnemigo, [this, enemigo, scene]() {
            scene->removeItem(enemigo);
            delete enemigo;
            enemies.removeOne(enemigo);
        });
    }


    //------------------------------
    Enemigo2* enemigo2 = new Enemigo2(ui->graphicsView);
    scene->addItem(enemigo2);
    enemigo2->setPos(600, 135);
    enemigo2->setJugador(jug1);

    // Conectar la señal de eliminarEnemigo
    connect(enemigo2, &Enemigo2::eliminarEnemigo, [this, enemigo2, scene]() {
        scene->removeItem(enemigo2);
        delete enemigo2;
    });

    jug1->setFlag(QGraphicsItem::ItemIsFocusable);
    jug1->setFocus();

    // Crea un cuadrado
    QGraphicsRectItem* cuadrado = new QGraphicsRectItem(0, 0, 200, 20);
    cuadrado->setBrush(Qt::red);
    scene->addItem(cuadrado);
    cuadrado->setPos(500, 230);

    QGraphicsRectItem* espacioEnem1 = new QGraphicsRectItem(0, 0, 200, 20);
    espacioEnem1->setBrush(Qt::red);
    scene->addItem(espacioEnem1);
    espacioEnem1->setPos(200, 210);

    QGraphicsRectItem* espacioEnem12 = new QGraphicsRectItem(0, 0, 80, 20);
    espacioEnem12->setBrush(Qt::red);
    scene->addItem(espacioEnem12);
    espacioEnem12->setPos(600, 80);


    QGraphicsRectItem* suelo = new QGraphicsRectItem(0, 0, 800, 20);
    suelo->setBrush(Qt::red);
    scene->addItem(suelo);
    suelo->setPos(0, 330);

    // Crea un temporizador para verificar colisiones
    QTimer* timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, jug1, &Jugador::verificarColisiones);
    timerColisiones->start(16); // Verifica colisiones cada 16
    connect(jug1->timerSalto, &QTimer::timeout, jug1, &Jugador::actualizarSalto);

}

MainWindow::~MainWindow()
{
    qDeleteAll(this->enemies);
    this->enemies.clear();
    delete ui;
}
