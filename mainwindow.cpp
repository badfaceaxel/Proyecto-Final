#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Particula.h"
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


    Particula *bola = new Particula();
    scene->addItem(bola);


    timer = new QTimer;
    //connect(timer,SIGNAL(timeout()),this,SLOT(hmov(*bola)));
    connect(timer, &QTimer::timeout, [=]() {
        hmov(bola);
    });
    timer->stop();


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    if (clic){
        ui->pushButton->setText("Hizo click");
        clic = false;
    }
    else{
        ui->pushButton->setText("Haga clic");
        clic = true;
    }
    if (timer->isActive()) timer->stop();
    else timer->start(100);

}

void MainWindow::hmov(Particula *bola)
{
    bola->moveBy(5,0);
}
