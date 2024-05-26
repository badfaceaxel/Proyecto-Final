#include "menuinicio.h"
#include "menuinicio.h"
#include "ui_menuinicio.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QShowEvent>

MenuInicio::MenuInicio(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuInicio)

{
    ui->setupUi(this);

    // Crear la escena y establecerla en QGraphicsView
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Cargar la imagen de fondo
    QPixmap backgroundImage(":/Imagenes/menu1.jpg");
    background = new QGraphicsPixmapItem(backgroundImage);
    scene->addItem(background);

    QPixmap titleImage(":/Imagenes/title.png");
    titleItem = new QGraphicsPixmapItem(titleImage);
    scene->addItem(titleItem);

    // Ajustar la posición del título en la escena
    titleItem->setPos(scene->width() / 2.5 - titleItem->boundingRect().width() / 2, scene->height() / 8);
    // Aumentar el tamaño del título
    titleItem->setScale(1.5);

    // Ajustar la vista para que la imagen de fondo ocupe todo el espacio disponible
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setFrameStyle(QFrame::NoFrame);



    // Ajustar la vista al tamaño de la ventana al inicio
    adjustBackground();
}

MenuInicio::~MenuInicio()
{
    delete ui;
}

void MenuInicio::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    adjustBackground();
}

void MenuInicio::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    adjustBackground();
}

void MenuInicio::adjustBackground()
{
    ui->graphicsView->fitInView(background, Qt::KeepAspectRatioByExpanding);
}
