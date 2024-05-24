#include "menuinicio.h"
#include "mainwindow.h"
#include "ui_menuinicio.h"
#include "Particula.h"
#include "Jugador.h"
#include <qdebug.h>
#include <QLabel>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsView>



MenuInicio::MenuInicio(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuInicio)
{
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this); // se debe crear una escena para manejar elementos gráficos
    scene->setSceneRect(0, 0, 800, 800);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(800 + 2 * ui->graphicsView->frameWidth(), 800 + 2 * ui->graphicsView->frameWidth());//manejar la relación de aspecto
    QPixmap backgroundImage(":/Imagenes/menu1.jpg");
    QGraphicsPixmapItem *background = scene->addPixmap(backgroundImage);
}

MenuInicio::~MenuInicio()
{
    delete ui;
}
