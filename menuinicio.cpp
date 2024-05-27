#include "menuinicio.h"
#include "ui_menuinicio.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QShowEvent>
//#include <QSound>
#include <QDebug>

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

    // Crear botones
    botonInicio = new QPushButton(this);
    botonScore = new QPushButton(this);
    botonSalir = new QPushButton(this);

    // Asignar imágenes
    botonInicio->setStyleSheet("QPushButton { border-image: url(:/Imagenes/BotonInicio.png); }");
    botonScore->setStyleSheet("QPushButton { border-image: url(:/Imagenes/BotonScore.png); }");
    botonSalir->setStyleSheet("QPushButton { border-image: url(:/Imagenes/BotonSalir.png); }");

    // Conectar los botones a sus slots
    connect(botonInicio, &QPushButton::clicked, this, &MenuInicio::onBotonInicioClicked);
    connect(botonScore, &QPushButton::clicked, this, &MenuInicio::onBotonScoreClicked);
    connect(botonSalir, &QPushButton::clicked, this, &MenuInicio::onBotonSalirClicked);

    // Ajustar la vista para que la imagen de fondo ocupe todo el espacio disponible
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setFrameStyle(QFrame::NoFrame);

    // Ajustar la vista al tamaño de la ventana al inicio
    adjustBackground();
    adjustButtons();
}

MenuInicio::~MenuInicio()
{
    delete ui;
}

void MenuInicio::adjustBackground()
{
    ui->graphicsView->fitInView(background, Qt::KeepAspectRatioByExpanding);
}

void MenuInicio::adjustButtons()
{
    int sceneWidth = ui->graphicsView->width();
    int sceneHeight = ui->graphicsView->height();

    // Calculamos una proporción basada en el tamaño inicial de la ventana
    float widthRatio = static_cast<float>(sceneWidth) / 600.0;  // 600 es el ancho inicial
    float heightRatio = static_cast<float>(sceneHeight) / 400.0; // 400 es el alto inicial

    int buttonWidth = 100 * widthRatio;
    int buttonHeight = 50 * heightRatio;

    /// Coordenadas y tamaño del botón "Inicio"
    botonInicio->setGeometry(sceneWidth / 2 - 220 * widthRatio, sceneHeight - 220 * heightRatio, buttonWidth, buttonHeight);

    // Coordenadas y tamaño del botón "Score"
    botonScore->setGeometry(sceneWidth / 2 - 220 * widthRatio, sceneHeight - 150 * heightRatio, buttonWidth, buttonHeight);

    // Coordenadas y tamaño del botón "Salir"
    botonSalir->setGeometry(sceneWidth / 2 - 220 * widthRatio, sceneHeight - 80 * heightRatio, buttonWidth, buttonHeight);
}

void MenuInicio::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    adjustBackground();
    adjustButtons();
}

void MenuInicio::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    adjustBackground();
    adjustButtons();
}

void MenuInicio::onBotonInicioClicked()
{
    //QSound::play(":/Sonidos/button_click.wav");
    // iniciar el juego
    qDebug() << "Botón Inicio presionado";
}

void MenuInicio::onBotonScoreClicked()
{
    //QSound::play(":/Sonidos/button_click.wav");
    //  mostrar el puntaje
    qDebug() << "Botón Score presionado";
}

void MenuInicio::onBotonSalirClicked()
{

    //QSound::play(":/Sonidos/button_click.wav");
    // Cerrar la aplicación
    QApplication::quit();
}
