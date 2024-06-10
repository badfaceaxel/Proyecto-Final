#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Particula.h"
#include "jugador.h"
#include "Enemigo1.h"
#include "Enemigo2.h"
#include "Jefe1.h"
#include "Jefe2.h"
#include <qdebug.h>
#include <QLabel>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) //La interfaz diseñada en Qt Designer
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
    crearEnemigos(ui->graphicsView, jug1, scene);

    // Conectar la señal de eliminarEnemigo para cada instancia
    for (Enemigo1* enemigo : qAsConst(enemies)) {
        connect(enemigo, &Enemigo1::eliminarEnemigo, [this, enemigo, scene]() {
            enemigo->setVisible(false);
            scene->removeItem(enemigo);
            delete enemigo;
            enemies.removeOne(enemigo);
        });
    }


    //------------------------------
    crearEnemigos2(ui->graphicsView, jug1, scene);

    // Conectar la señal de eliminarEnemigo
    for (Enemigo2* enemigo2 : enemies2) {
        connect(enemigo2, &Enemigo2::eliminarEnemigo, [this, enemigo2, scene]() {
            //qDebug() << "Entrando al slot eliminarEnemigo de Enemigo2";
            enemigo2->setVisible(false);
            //qDebug() << "Llamando a eliminarDardo()";
            enemigo2->eliminarDardo(); // Llamar a eliminarDardo() antes de eliminar al enemigo2
            //qDebug() << "Dardo eliminado (si existía)";
            scene->removeItem(enemigo2);

            // Desconectar la conexión adicional a la señal eliminarEnemigo
            disconnect(enemigo2, &Enemigo2::eliminarEnemigo, nullptr, nullptr);

            // Desconectar la señal eliminarEnemigo
            disconnect(enemigo2, &Enemigo2::eliminarEnemigo, this, nullptr);

            delete enemigo2;
            enemies2.removeOne(enemigo2);
            //qDebug() << "Enemigo2 eliminado";
        });
    }

    //------------------------------
    //JEFES
    Jefe1* jefe1 = new Jefe1(ui->graphicsView);
    scene->addItem(jefe1);
    jefe1->setPos(500, 200);
    jefe1->setJugador(jug1);

    Jefe2* jefe2 = new Jefe2(ui->graphicsView);
    scene->addItem(jefe2);
    jefe2->setPos(500, 200);
    jefe2->setJugador(jug1);


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
    espacioEnem1->setPos(200, 220);

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

void MainWindow::crearEnemigos(QGraphicsView* view, Jugador* jugador, QGraphicsScene* scene) {
    QVector<QPointF> posicionesIniciales = {
        QPointF(600, 235),
        QPointF(200, 130),
        QPointF(600, -10)
    };

    for (int i = 0; i < posicionesIniciales.size(); ++i) {
        Enemigo1* enemigo = new Enemigo1(view);
        scene->addItem(enemigo);
        enemigo->establecerPosicionInicial(posicionesIniciales[i].x(), posicionesIniciales[i].y());
        enemigo->setJugador(jugador);

        // Iniciar el temporizador de movimiento solo para la primera y la tercera instancia
        if (i == 0) {
            enemigo->timerMovimiento->start(50);
        }

        enemies.append(enemigo);
    }
}

void MainWindow::crearEnemigos2(QGraphicsView* view, Jugador* jugador, QGraphicsScene* scene) {
    QVector<QPointF> posicionesIniciales = {
        QPointF(600, 135),
        QPointF(240, 130),
        QPointF(620, -10)
    };

    for (const QPointF& posicion : posicionesIniciales) {
        Enemigo2* enemigo2 = new Enemigo2(view);
        scene->addItem(enemigo2);
        enemigo2->setPos(posicion);
        enemigo2->setJugador(jugador);

        // Conectar la señal de eliminarEnemigo
        connect(enemigo2, &Enemigo2::eliminarEnemigo, [this, enemigo2, scene]() {
            //qDebug() << "Entrando al slot eliminarEnemigo de Enemigo2";
            enemigo2->setVisible(false);
            //qDebug() << "Llamando a eliminarDardo()";
            enemigo2->eliminarDardo(); // Llamar a eliminarDardo() antes de eliminar al enemigo2
            //qDebug() << "Dardo eliminado (si existía)";
            scene->removeItem(enemigo2);

            // Detener y eliminar el temporizador timerDardo
            if (enemigo2->timerDardo != nullptr) {
                enemigo2->timerDardo->stop();
                delete enemigo2->timerDardo;
                enemigo2->timerDardo = nullptr;
            }

            // Eliminar el dardo si aún existe
            if (enemigo2->dardo != nullptr) {
                scene->removeItem(enemigo2->dardo);
                delete enemigo2->dardo;
                enemigo2->dardo = nullptr;
            }

            // Desconectar la señal eliminarEnemigo
            disconnect(enemigo2, &Enemigo2::eliminarEnemigo, nullptr, nullptr);

            delete enemigo2;
            //qDebug() << "Enemigo2 eliminado";
        });

        enemies2.append(enemigo2);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
