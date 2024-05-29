#include "menuinicio.h"
#include "ui_menuinicio.h"

MenuInicio::MenuInicio(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MenuInicio)
{
    ui->setupUi(this);

    // Crear la escena y establecerla en QGraphicsView
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    // Cargar la imagen de fondo
    QPixmap backgroundImage(":/Media/menu1.jpg");
    background = new QGraphicsPixmapItem(backgroundImage);
    scene->addItem(background);

    // Ajustar la vista para que la imagen de fondo ocupe todo el espacio disponible
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    ui->graphicsView->setFrameStyle(QFrame::NoFrame);

    //Cargar titulo
    QPixmap titleImage(":/Media/title.png");
    titleItem = new QGraphicsPixmapItem(titleImage);
    scene->addItem(titleItem);

    // Ajustar la posición del título en la escena
    titleItem->setPos(scene->width() / 2.5 - titleItem->boundingRect().width() / 2, scene->height() / 8);
    // Aumentar el tamaño del título
    titleItem->setScale(1.5);

    // Cargar y redimensionar la imagen de la firma
    QPixmap signImage("/Media/Firma.png");
    signItem = new QGraphicsPixmapItem(signImage);
    scene->addItem(signItem);

    // Crear botones
    botonInicio = new QPushButton(this);
    botonScore = new QPushButton(this);
    botonSalir = new QPushButton(this);

    // Cargar imágenes normales y rojas de los botones
    botonInicioNormal.load("/Media/BotonInicio.png");
    botonInicioRojo.load(":/Media/BotonInicioRojo.png");
    botonScoreNormal.load(":/Media/BotonScore.png");
    botonScoreRojo.load(":/Media/BotonScoreRojo.png");
    botonSalirNormal.load(":/Media/BotonSalir.png");
    botonSalirRojo.load(":/Media/BotonSalirRojo.png");

    // Asignar imágenes normales
    botonInicio->setStyleSheet("QPushButton { border-image: url(:/Media/BotonInicio.png); }");
    botonScore->setStyleSheet("QPushButton { border-image: url(:/Media/BotonScore.png); }");
    botonSalir->setStyleSheet("QPushButton { border-image: url(:/Media/BotonSalir.png); }");

    // Conectar señales y ranuras
    connect(botonInicio, &QPushButton::clicked, this, &MenuInicio::onBotonInicioClicked);
    connect(botonScore, &QPushButton::clicked, this, &MenuInicio::onBotonScoreClicked);
    connect(botonSalir, &QPushButton::clicked, this, &MenuInicio::onBotonSalirClicked);

    botonInicio->setMouseTracking(true);
    botonScore->setMouseTracking(true);
    botonSalir->setMouseTracking(true);

    // Instalar filtro de eventos para los botones
    botonInicio->installEventFilter(this);
    botonScore->installEventFilter(this);
    botonSalir->installEventFilter(this);

    // Cargar sonidos
    hoverSound = new QSoundEffect(this);
    hoverSound->setSource(QUrl::fromLocalFile(":/Media/Select1.wav"));
    hoverSound->setVolume(0.25f);

    clickSound = new QSoundEffect(this);
    clickSound->setSource(QUrl::fromLocalFile(":/Media/Click1.wav"));
    clickSound->setVolume(0.25f);

    // Ajustar la vista al tamaño de la ventana al inicio
    adjustBackground();
    adjustButtons();
    adjustSign();
}

MenuInicio::~MenuInicio()
{
    delete ui;
    delete scene;
    delete background;
    delete titleItem;
    delete signItem;
    delete botonInicio;
    delete botonScore;
    delete botonSalir;

}

void MenuInicio::adjustBackground()
{
    ui->graphicsView->fitInView(background, Qt::KeepAspectRatioByExpanding);
}

void MenuInicio::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    adjustBackground();
    adjustButtons();
    adjustSign();
}

void MenuInicio::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    adjustBackground();
    adjustButtons();
    adjustSign();
}

void MenuInicio::adjustButtons()
{
    int sceneWidth = ui->graphicsView->width();
    int sceneHeight = ui->graphicsView->height();

    // Calculamos una proporción basada en el tamaño inicial de la ventana
    float widthRatio = static_cast<float>(sceneWidth) / 800.0;  // 600 es el ancho inicial
    float heightRatio = static_cast<float>(sceneHeight) / 600.0; // 400 es el alto inicial

    int buttonWidth = 120 * widthRatio;
    int buttonHeight = 50 * heightRatio;

    // Coordenadas y tamaño del botón "Inicio"
    botonInicio->setGeometry(sceneWidth / 2 - 270 * widthRatio, sceneHeight - 300 * heightRatio, buttonWidth, buttonHeight);

    // Coordenadas y tamaño del botón "Score"
    botonScore->setGeometry(sceneWidth / 2 - 270 * widthRatio, sceneHeight - 200 * heightRatio, buttonWidth, buttonHeight);

    // Coordenadas y tamaño del botón "Salir"
    botonSalir->setGeometry(sceneWidth / 2 - 270 * widthRatio, sceneHeight - 100 * heightRatio, buttonWidth, buttonHeight);
}

void MenuInicio::onBotonInicioClicked()
{
    // iniciar el juego
    clickSound->play();
    qDebug() << "Botón Inicio presionado";
}

void MenuInicio::onBotonScoreClicked()
{
    // mostrar el puntaje
    clickSound->play();
    qDebug() << "Botón Score presionado";
}

void MenuInicio::onBotonSalirClicked()
{
    clickSound->play();
    // Cerrar la aplicación
    QApplication::quit();
}

bool MenuInicio::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::HoverEnter) {
        if (obj == botonInicio) {
            hoverSound->play();
            botonInicio->setStyleSheet("QPushButton { border-image: url(:/Media/BotonInicioRojo.png); }");
        } else if (obj == botonScore) {
            hoverSound->play();
            botonScore->setStyleSheet("QPushButton { border-image: url(:/Media/BotonScoreRojo.png); }");
        } else if (obj == botonSalir) {
            hoverSound->play();
            botonSalir->setStyleSheet("QPushButton { border-image: url(:/Media/BotonSalirRojo.png); }");
        }
    } else if (event->type() == QEvent::HoverLeave) {
        if (obj == botonInicio) {
            botonInicio->setStyleSheet("QPushButton { border-image: url(:/Media/BotonInicio.png); }");
        } else if (obj == botonScore) {
            botonScore->setStyleSheet("QPushButton { border-image: url(:/Media/BotonScore.png); }");
        } else if (obj == botonSalir) {
            botonSalir->setStyleSheet("QPushButton { border-image: url(:/Media/BotonSalir.png); }");
        }
    }
    return QWidget::eventFilter(obj, event);
}

void MenuInicio::adjustSign()
{
    int sceneWidth = ui->graphicsView->width();
    int sceneHeight = ui->graphicsView->height();

    // Escalar la firma basada en el tamaño de la ventana
    float scaleRatio = static_cast<float>(sceneWidth) / 800.0;  // Cambiar este valor según sea necesario

    QPixmap signImage(":/Media/Firma.png");
    QPixmap scaledSignImage = signImage.scaled(200 * scaleRatio, 50 * scaleRatio, Qt::KeepAspectRatio); // Ajustar dimensiones según sea necesario
    signItem->setPixmap(scaledSignImage);

    // Colocar la firma en la esquina inferior derecha
    signItem->setPos(30, 5); // Ajustar el offset (10) según sea necesario
}