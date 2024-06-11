#include "level2.h"
#include <QGraphicsView>
#include "Enemigo2.h"
#include "enemigo1.h"
#include "jugador.h"
#include "jugador.h"    //CambioAxel
#include "menuinicio.h" // Agrega esta línea aquí
#include "ui_level2.h"
#include "Jefe1.h"
#include "Jefe2.h"

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
    player->setLimites(800, 4000);

    //CORAZONES Y PUNTUACION
    QPixmap corazonPixmap(":/Media/corazon.png");
    corazonPixmap = corazonPixmap.scaledToWidth(corazonPixmap.width() * 0.15, Qt::SmoothTransformation);


    // Crea los corazones y agrega cada uno a la escena
    for (int i = 0, j = 800; i < 5; ++i) {
        QGraphicsPixmapItem* corazon = new QGraphicsPixmapItem(corazonPixmap);
        corazon->setPos(j, 10); // Establece la posición del corazón
        j = j + 70;
        scene->addItem(corazon);
        corazones.append(corazon);
    }

    qDebug() << "Corazones en el vector:" << corazones.size();

    // Crear el objeto QGraphicsTextItem para la puntuación
    puntuacionTexto = new QGraphicsTextItem();
    QFont font("Arial", 20); // Establece la fuente y el tamaño del texto
    puntuacionTexto->setFont(font);
    puntuacionTexto->setDefaultTextColor(Qt::red); // Establecer el color del texto a blanco
    puntuacionTexto->setPos(600, 0); // Establecer la posición del texto
    scene->addItem(puntuacionTexto);
    scene->update();

    // Conectar la señal puntuacionCambiada a la función para actualizar el texto
    connect(player, &Jugador::puntuacionCambiada, this, &Level2::actualizarPuntuacionTexto);

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
    Jefe1* jefe1 = new Jefe1(ui->graphicsView);
    scene->addItem(jefe1);
    jefe1->setPos(500, 200);
    jefe1->setJugador(player);

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

    connect(player, &Jugador::vidaCambiada, this, &Level2::actualizarCorazones);
    connect(player, &Jugador::posicionCambiada, this, &Level2::moverCorazones);

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

    // Liberar la memoria de los corazones
    qDeleteAll(corazones);
    corazones.clear();
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

void Level2::ajustarVistaMundo() {
    int playerX = player->getX();
    int offsetX = playerX - anchoVentana / (2 * ui->graphicsView->transform().m11());

    // Mantener la vista dentro de los límites del mundo
    if (offsetX < 0) offsetX = 0;
    if (offsetX > anchoTotalMundo - anchoVentana / ui->graphicsView->transform().m11())
        offsetX = anchoTotalMundo - anchoVentana / ui->graphicsView->transform().m11();

    desplazamientoHorizontal = offsetX; // Asignar el desplazamiento horizontal

    // Establecer el área visible
    ui->graphicsView->setSceneRect(offsetX, 0, anchoVentana / ui->graphicsView->transform().m11(), ui->graphicsView->height() / ui->graphicsView->transform().m11());

    // Centrar en el jugador
    ui->graphicsView->centerOn(playerX, ui->graphicsView->height() / (2 * ui->graphicsView->transform().m11()));

    // Actualizar la posición del texto de la puntuación
    puntuacionTexto->setPos(offsetX - 200, 15);


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

void Level2::crearEnemigos2(QGraphicsView* view, Jugador* jugador, QGraphicsScene* scene) {
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

void Level2::actualizarCorazones(int nuevaVida) {
    // Obtener el número de corazones que se deben mostrar
    int corazonesAMostrar = (nuevaVida / 20) + 1;

    // Ocultar o mostrar los corazones según la nueva vida
    for (int i = 0; i < corazones.size(); ++i) {
        if (i < corazonesAMostrar) {
            corazones[i]->setVisible(true);
        } else {
            corazones[i]->setVisible(false);
        }
    }
}

void Level2::moverCorazones() {
    ajustarVistaMundo(); // Actualiza el desplazamientoHorizontal

    // Ocultar o mostrar los corazones según la nueva vida
    for (int i = 0; i < corazones.size(); ++i) {
        if (corazones[i]->isVisible()) {
            corazones[i]->setPos(desplazamientoHorizontal + 10 + i * (corazones[i]->pixmap().width() + 5), 10);
        }
    }
}

void Level2::actualizarPuntuacionTexto(int nuevaPuntuacion) {
    // Actualizar el texto del objeto QGraphicsTextItem con la nueva puntuación
    puntuacionTexto->setPlainText(QString("Score: %1").arg(nuevaPuntuacion));
    puntuacionTexto->setPos(600, 10); // Establecer la posición del texto
}
