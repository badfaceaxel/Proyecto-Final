#include "level1.h"
#include "jugador.h"
#include "enemigo1.h"
#include "ui_level1.h"
#include "menuinicio.h"  // Agrega esta línea aquí
#include "jugador.h"     //CambioAxel
#include "Enemigo2.h"
#include "Jefe1.h"
#include "Jefe2.h"

Level1::Level1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Level1)
    , menuInicio(nullptr)  // Inicializa level2 a nullptr
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this); // se debe crear una escena para manejar elementos gráficos
    ui->graphicsView->setScene(scene);

    // Cargar la imagen de fondo        //CambioAxel
    QPixmap backgroundImage(":/Media/background.jpg");     //Ponga la ruta segun como usted la tenga
    background = new QGraphicsPixmapItem(backgroundImage);
    scene->addItem(background);

    // Guardar el tamaño original del fondo
    backgroundWidth = backgroundImage.width();
    backgroundHeight = backgroundImage.height();


    anchoTotalMundo = backgroundImage.width();     //CambioEscena
    anchoVentana = ui->graphicsView->width();      //CambioEscena

    // Set initial view to show the first part of the background
    ui->graphicsView->setSceneRect(0, 0, 1600, backgroundImage.height());
    ui->graphicsView->fitInView(0, 0, 1600, backgroundImage.height(), Qt::KeepAspectRatioByExpanding);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);    //CambioEscena
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);     //CambioEscena

    // Crea el menú
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Crea el menú "Archivo"
    QMenu *menuArchivo = menuBar->addMenu("&Opciones");

    // Crea la acción "Volver al Menú Principal"
    QAction *accionVolverMenuPrincipal = new QAction("&Volver al Menú Principal", this);
    connect(accionVolverMenuPrincipal, &QAction::triggered, this, &Level1::volverMenuPrincipal);
    menuArchivo->addAction(accionVolverMenuPrincipal);

    // Crea la acción "Salir"
    QAction *accionSalir = new QAction("&Salir", this);
    connect(accionSalir, &QAction::triggered, this, &QWidget::close);
    menuArchivo->addAction(accionSalir);

    // Agregar personajes y otros elementos a la escena
    player = new Jugador(ui->graphicsView);       //CambioAxel - Usted lo tenia como jug1, lo cambie a player

    scene->addItem(player);
    player->setPos(10, 450);

    connect(player, &Jugador::posicionCambiada, this, &Level1::ajustarVistaMundo);  //CambioEscena
    player->setLimites(800, 4000);        //CambioEscena

    //qDebug() << ui->graphicsView->size()<<" "<<scene->sceneRect();

    // Crear enemigos
    crearEnemigos(ui->graphicsView, player, scene);

    // Conectar la señal de eliminarEnemigo para cada instancia
    for (Enemigo1* enemigo : qAsConst(enemies)) {
        connect(enemigo, &Enemigo1::eliminarEnemigo, [this, enemigo]() {
            enemigo->setVisible(false);
            this->scene->removeItem(enemigo);
            delete enemigo;
            enemies.removeOne(enemigo);
        });
    }


    //------------------------------
    crearEnemigos2(ui->graphicsView, player, scene);

    // Conectar la señal de eliminarEnemigo
    for (Enemigo2* enemigo2 : enemies2) {
        connect(enemigo2, &Enemigo2::eliminarEnemigo, [this, enemigo2]() {
            //qDebug() << "Entrando al slot eliminarEnemigo de Enemigo2";
            enemigo2->setVisible(false);
            //qDebug() << "Llamando a eliminarDardo()";
            enemigo2->eliminarDardo(); // Llamar a eliminarDardo() antes de eliminar al enemigo2
            //qDebug() << "Dardo eliminado (si existía)";
            this->scene->removeItem(enemigo2);

            // Desconectar la conexión adicional a la señal eliminarEnemigo
            disconnect(enemigo2, &Enemigo2::eliminarEnemigo, nullptr, nullptr);

            // Desconectar la señal eliminarEnemigo
            disconnect(enemigo2, &Enemigo2::eliminarEnemigo, this, nullptr);

            delete enemigo2;
            enemies2.removeOne(enemigo2);
            //qDebug() << "Enemigo2 eliminado";
        });
    }

    //JEFES
   /*Jefe1* jefe1 = new Jefe1(ui->graphicsView);
    scene->addItem(jefe1);
    jefe1->setPos(1300, 200);
    jefe1->setJugador(player);

    Jefe2* jefe2 = new Jefe2(ui->graphicsView);
    scene->addItem(jefe2);
    jefe2->setPos(1300, 200);
    jefe2->setJugador(player);*/

    // Agregar personajes y otros elementos a la escena

    player->setFlag(QGraphicsItem::ItemIsFocusable);    ////
    player->setFocus();  /////jug1

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

    QGraphicsRectItem* espacioEnem123 = new QGraphicsRectItem(0, 0, 200, 20);
    espacioEnem123->setBrush(brushPiedra);
    scene->addItem(espacioEnem123);
    espacioEnem123->setPos(1700, 230);

    QGraphicsRectItem* espacioEnem233 = new QGraphicsRectItem(0, 0, 170, 20);
    espacioEnem233->setBrush(brushPiedra);
    scene->addItem(espacioEnem233);
    espacioEnem233->setPos(2000, 150);

    QGraphicsRectItem* espacioEnem223 = new QGraphicsRectItem(0, 0, 150, 20);
    espacioEnem223->setBrush(brushPiedra);
    scene->addItem(espacioEnem223);
    espacioEnem223->setPos(2300, 220);

    QGraphicsRectItem* espacioEnem323 = new QGraphicsRectItem(0, 0, 150, 20);
    espacioEnem323->setBrush(brushPiedra);
    scene->addItem(espacioEnem323);
    espacioEnem323->setPos(2500, 120);

    QGraphicsRectItem* espacioEnem423 = new QGraphicsRectItem(0, 0, 150, 20);
    espacioEnem423->setBrush(brushPiedra);
    scene->addItem(espacioEnem423);
    espacioEnem423->setPos(2700, 190);

    QGraphicsRectItem* espacioEnem523 = new QGraphicsRectItem(0, 0, 150, 20);
    espacioEnem523->setBrush(brushPiedra);
    scene->addItem(espacioEnem523);
    espacioEnem523->setPos(3000, 230);

    QGraphicsRectItem* espacioEnem533 = new QGraphicsRectItem(0, 0, 180, 20);
    espacioEnem533->setBrush(brushPiedra);
    scene->addItem(espacioEnem533);
    espacioEnem533->setPos(3250, 230);

    QGraphicsRectItem* espacioEnem623 = new QGraphicsRectItem(0, 0, 150, 20);
    espacioEnem623->setBrush(brushPiedra);
    scene->addItem(espacioEnem623);
    espacioEnem623->setPos(3600, 180);

    QGraphicsRectItem* espacioEnem723 = new QGraphicsRectItem(0, 0, 250, 20);
    espacioEnem723->setBrush(brushPiedra);
    scene->addItem(espacioEnem723);
    espacioEnem723->setPos(3900, 220);



    QGraphicsRectItem* suelo = new QGraphicsRectItem(0, 0, 3100, 20);
    suelo->setBrush(brushPiedra);
    scene->addItem(suelo);
    suelo->setPos(0, 330);

    QGraphicsRectItem* suelo2 = new QGraphicsRectItem(0, 0, 1700, 20);
    suelo2->setBrush(brushPiedra);
    scene->addItem(suelo2);
    suelo2->setPos(3400, 330);

    // Crea un temporizador para verificar colisiones
    QTimer* timerColisiones = new QTimer(this);
    connect(timerColisiones, &QTimer::timeout, player, &Jugador::verificarColisiones);
    timerColisiones->start(16); // Verifica colisiones cada 16
    connect(player->timerSalto, &QTimer::timeout, player, &Jugador::actualizarSalto);

    adjustBackground();


}

Level1::~Level1()
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

void Level1::adjustBackground() {
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


void Level1::resizeEvent(QResizeEvent* event)    //CambioAxel
{
    QMainWindow::resizeEvent(event);
    ajustarVistaMundo();
    adjustBackground();
}

void Level1::showEvent(QShowEvent* event)     //CambioAxel
{
    QWidget::showEvent(event);
    ajustarVistaMundo();
    adjustBackground();
}

void Level1::ajustarVistaMundo() {
    int playerX = player->getX();
    int offsetX = playerX - anchoVentana / (2 * ui->graphicsView->transform().m11());

    // Mantener la vista dentro de los límites del mundo
    if (offsetX < 0) offsetX = 0;
    if (offsetX > anchoTotalMundo - anchoVentana / ui->graphicsView->transform().m11())
        offsetX = anchoTotalMundo - anchoVentana / ui->graphicsView->transform().m11();

    // Establecer el área visible
    ui->graphicsView->setSceneRect(offsetX, 0, anchoVentana / ui->graphicsView->transform().m11(), ui->graphicsView->height() / ui->graphicsView->transform().m11());

    // Centrar en el jugador
    ui->graphicsView->centerOn(playerX, ui->graphicsView->height() / (2 * ui->graphicsView->transform().m11()));


}

void Level1::crearEnemigos(QGraphicsView* view, Jugador* jugador, QGraphicsScene* scene) {
    QVector<QPointF> posicionesIniciales = {
        QPointF(1400, 235),
        QPointF(1000, 120),
        QPointF(1400, -10),
        QPointF(2000, 55),
        QPointF(2300, 125),
        QPointF(2700, 95),
        QPointF(3050, 135),
        QPointF(3600, 85),
        QPointF(3900, 125),
        QPointF(3700, 235),
        QPointF(3900, 235),
        QPointF(2000, 235),// se mueven
        QPointF(2700, 235),
        QPointF(3100, 235)

    };

    for (int i = 0; i < posicionesIniciales.size(); ++i) {
        Enemigo1* enemigo = new Enemigo1(view);
        scene->addItem(enemigo);
        enemigo->establecerPosicionInicial(posicionesIniciales[i].x(), posicionesIniciales[i].y());
        enemigo->setJugador(jugador);

        // Iniciar el temporizador de movimiento solo para la primera y la tercera instancia
        if (i == 0 || i == 11 || i == 12 || i == 13) {
            enemigo->timerMovimiento->start(50);
        }

        enemies.append(enemigo);
    }
}

void Level1::crearEnemigos2(QGraphicsView* view, Jugador* jugador, QGraphicsScene* scene) {
    QVector<QPointF> posicionesIniciales = {
        QPointF(1400, 135),
        QPointF(1800, 135),
        QPointF(2500, 25),
        QPointF(3250, 135),
        QPointF(4000, 125)

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

void Level1::volverMenuPrincipal()
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


