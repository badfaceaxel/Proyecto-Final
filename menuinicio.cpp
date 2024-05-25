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
    //, labelTitle(new QLabel(this))  // Inicializar labelTitle
{
    ui->setupUi(this);

    // Crear la escena y establecerla en QGraphicsView
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Cargar la imagen de fondo
    QPixmap backgroundImage(":/Imagenes/menu1.jpg");
    background = new QGraphicsPixmapItem(backgroundImage);
    scene->addItem(background);

    // Ajustar la vista para que la imagen de fondo ocupe todo el espacio disponible
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setFrameStyle(QFrame::NoFrame);

    // Cargar y mostrar la imagen del título
    //QPixmap titleImage(":/Imagenes/title.png"); // Asegúrate de que la ruta sea correcta
    //labelTitle->setPixmap(titleImage);
    //labelTitle->setAlignment(Qt::AlignCenter);

    // Colocar labelTitle en el layout
    //QVBoxLayout *layout = new QVBoxLayout(this);
    //layout->addWidget(labelTitle);
    //layout->addWidget(ui->graphicsView);
    //setLayout(layout);

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
