#include "level2.h"
#include <QGraphicsView>
#include "Enemigo2.h"
#include "enemigo1.h"
#include "jugador.h"
#include "jugador.h"    //CambioAxel
#include "menuinicio.h" // Agrega esta línea aquí
#include "ui_level2.h"

Level2::Level2(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Level2)
    , menuInicio(nullptr)  // Inicializa level2 a nullptr

{
    ui->setupUi(this);

    scene = new QGraphicsScene(this); // se debe crear una escena para manejar elementos gráficos
    ui->graphicsView->setScene(scene);

    // Cargar la imagen de fondo        //CambioAxel
    QPixmap backgroundImage(":/Media/background2.png"); //Ponga la ruta segun como usted la tenga
    background = new QGraphicsPixmapItem(backgroundImage);
    scene->addItem(background);

    // Guardar el tamaño original del fondo
    backgroundWidth = backgroundImage.width();
    backgroundHeight = backgroundImage.height();

    anchoTotalMundo = backgroundImage.width(); //CambioEscena
    anchoVentana = ui->graphicsView->width();  //CambioEscena

    // Set initial view to show the first part of the background
    ui->graphicsView->setSceneRect(0, 0, 1600, backgroundImage.height());
    ui->graphicsView->fitInView(0, 0, 1600, backgroundImage.height(), Qt::KeepAspectRatioByExpanding);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //CambioEscena
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   //CambioEscena

    // Crea el menú
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Crea el menú "Archivo"
    QMenu *menuArchivo = menuBar->addMenu("&Opciones");

    // Crea la acción "Volver al Menú Principal"
    QAction *accionVolverMenuPrincipal = new QAction("&Volver al Menú Principal", this);
    connect(accionVolverMenuPrincipal, &QAction::triggered, this, &Level2::volverMenuPrincipal);
    menuArchivo->addAction(accionVolverMenuPrincipal);

    // Crea la acción "Salir"
    QAction *accionSalir = new QAction("&Salir", this);
    connect(accionSalir, &QAction::triggered, this, &QWidget::close);
    menuArchivo->addAction(accionSalir);

    // Agregar personajes y otros elementos a la escena
    player = new Jugador(
        ui->graphicsView); //CambioAxel - Usted lo tenia como jug1, lo cambie a player

    scene->addItem(player);
    player->setPos(10, 450);

    connect(player, &Jugador::posicionCambiada, this, &Level2::ajustarVistaMundo); //CambioEscena
    player->setLimites(800, 4000);                                                 //CambioEscena

    //qDebug() << ui->graphicsView->size()<<" "<<scene->sceneRect();

    // Crear enemigos
    crearEnemigos(ui->graphicsView, player, scene);

    // Conectar la señal de eliminarEnemigo para cada instancia
    for (Enemigo1 *enemigo : qAsConst(enemies)) {
        connect(enemigo, &Enemigo1::eliminarEnemigo, [this, enemigo]() {
            enemigo->setVisible(false);
            this->scene->removeItem(enemigo);
            delete enemigo;
            enemies.removeOne(enemigo);
        });
    }

    //------------------------------
    Enemigo2 *enemigo2 = new Enemigo2(ui->graphicsView);
    scene->addItem(enemigo2);
    enemigo2->setPos(600, 135);
    enemigo2->setJugador(player);

    // Conectar la señal de eliminarEnemigo
    connect(enemigo2, &Enemigo2::eliminarEnemigo, [this, enemigo2]() {
        this->scene->removeItem(enemigo2);
        delete enemigo2;
    });

    // Agregar personajes y otros elementos a la escena

    player->setFlag(QGraphicsItem::ItemIsFocusable); ////
    player->setFocus();                              /////jug1

    // Carga la textura de piedra desde un archivo
    QPixmap piedraTextura(":/Media/Piedra.png"); // Reemplaza ":/Media/piedra.png" con la ruta de tu imagen
    piedra = new QGraphicsPixmapItem(piedraTextura);

    // Crea un pincel con la textura de piedra
    QBrush brushPiedra(piedraTextura);

    // Crea un cuadrado
    QGraphicsRectItem* cuadrado = new QGraphicsRectItem(0, 0, 200, 20);
    cuadrado->setBrush(brushPiedra);
    scene->addItem(cuadrado);
    cuadrado->setPos(1300, 230);

    QGraphicsRectItem* espacioEnem1 = new QGraphicsRectItem(0, 0, 200, 20);
    espacioEnem1->setBrush(brushPiedra);
    scene->addItem(espacioEnem1);
    espacioEnem1->setPos(1000, 210);

    QGraphicsRectItem* espacioEnem12 = new QGraphicsRectItem(0, 0, 80, 20);
    espacioEnem12->setBrush(brushPiedra);
    scene->addItem(espacioEnem12);
    espacioEnem12->setPos(1400, 80);

    QGraphicsRectItem* suelo = new QGraphicsRectItem(0, 0, 800, 20);
    suelo->setBrush(brushPiedra);
    scene->addItem(suelo);
    suelo->setPos(800, 330);

    // Crea un temporizador para verificar colisiones
    QTimer *timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, player, &Jugador::verificarColisiones);
    timerColisiones->start(16); // Verifica colisiones cada 16
    connect(player->timerSalto, &QTimer::timeout, player, &Jugador::actualizarSalto);

    adjustBackground();
}

Level2::~Level2()
{
    delete ui;
    delete scene;
    delete background;
    if (menuInicio) {
        delete menuInicio;
        menuInicio = nullptr;
    }

    qDeleteAll(this->enemies);
    this->enemies.clear();
}

void Level2::adjustBackground()
{
    QRectF sceneRect = ui->graphicsView->sceneRect();

    // Factor para hacer la escena más grande que la vista
    qreal zoomOutFactor = 0.67; // Ajusta este valor para alejar más o menos
    qreal newWidth = ui->graphicsView->width() * zoomOutFactor;
    qreal newHeight = ui->graphicsView->height() * zoomOutFactor;

    // Calcula el nuevo rectángulo de la escena
    QRectF newSceneRect(sceneRect.x(), sceneRect.y(), newWidth, newHeight);
    ui->graphicsView->fitInView(newSceneRect, Qt::KeepAspectRatio);

    // Centra la vista en la escena
    ui->graphicsView->centerOn(sceneRect.center());
}

void Level2::resizeEvent(QResizeEvent *event) //CambioAxel
{
    QMainWindow::resizeEvent(event);
    adjustBackground();
}

void Level2::showEvent(QShowEvent *event) //CambioAxel
{
    QWidget::showEvent(event);
    adjustBackground();
}

void Level2::ajustarVistaMundo()
{
    int playerX = player->getX();
    int offsetX = playerX - anchoVentana / (2 * ui->graphicsView->transform().m11());

    // Mantener la vista dentro de los límites del mundo
    if (offsetX < 0)
        offsetX = 0;
    if (offsetX > anchoTotalMundo - anchoVentana / ui->graphicsView->transform().m11())
        offsetX = anchoTotalMundo - anchoVentana / ui->graphicsView->transform().m11();

    // Establecer el área visible
    ui->graphicsView->setSceneRect(offsetX,
                                   0,
                                   anchoVentana / ui->graphicsView->transform().m11(),
                                   ui->graphicsView->height() / ui->graphicsView->transform().m11());

    // Centrar en el jugador
    ui->graphicsView->centerOn(playerX,
                               ui->graphicsView->height()
                                   / (2 * ui->graphicsView->transform().m11()));
}

void Level2::crearEnemigos(QGraphicsView *view, Jugador *jugador, QGraphicsScene *scene)
{
    QVector<QPointF> posicionesIniciales = {
        QPointF(1400, 235),
        QPointF(1000, 120),
        QPointF(1400, -10),
        QPointF(1600, -10)
    };

    for (int i = 0; i < posicionesIniciales.size(); ++i) {
        Enemigo1 *enemigo = new Enemigo1(view);
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

void Level2::volverMenuPrincipal()
{
    // Crear una instancia de MenuInicio si no existe
    if (!menuInicio) {
        menuInicio = new MenuInicio(this);
    }

    // Mostrar el MenuInicio
    menuInicio->show();

    // Cerrar el Level1
    this->hide();
}
