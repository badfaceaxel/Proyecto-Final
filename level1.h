#ifndef LEVEL1_H
#define LEVEL1_H

#include <QMainWindow>
#include <QTimer>
#include "Particula.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QResizeEvent>        //CambioAxel
#include <QShowEvent>          //CambioAxel
#include "jugador.h"
#include "Enemigo1.h"
#include "Enemigo2.h"
#include <QMenuBar>
#include <QGraphicsTextItem>
#include "perderdialog.h" // Incluir el nuevo diálogo


// Agrega esta línea para la declaración anticipada
class MenuInicio;  // Esto le dice al compilador que MenuInicio es una clase       //CambioAxel
class Level2;
class NivelCompletadoDialog;
class PerderDialog;

namespace Ui {
class Level1;
}

class Level1 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Level1(QWidget *parent = nullptr);
    ~Level1();
    bool clic;
    Jugador* getJugador() { return player; }  // Agrega esta función /////////CambioAxel
    void volverMenuPrincipal();
    void actualizarPuntuacionTexto(int nuevaPuntuacion);
    void actualizarPosicionJugador();


protected:
    void resizeEvent(QResizeEvent *event) override;    //CambioAxel
    void showEvent(QShowEvent *event) override;        //CambioAxel

private slots:
    void actualizarCorazones(int nuevaVida);
    void moverCorazones();
    void mostrarVentanaPerdiste(); // Declarar la función
    void mostrarDialogoNivelCompletado();
    void continuarNivel2();
//    void volverMenuPrincipal();


private:
    Ui::Level1 *ui;
    QTimer *timer;
    QList<Enemigo1*> enemies;
    QVector<Enemigo2*> enemies2;
    void crearEnemigos(QGraphicsView* view, Jugador* jugador, QGraphicsScene* scene);
    void crearEnemigos2(QGraphicsView* view, Jugador* jugador, QGraphicsScene* scene);

    Jugador *player;   //CambioAxel

    QVector<QGraphicsPixmapItem*> corazones;
    QGraphicsTextItem *puntuacionTexto;

    //FONDO
    QGraphicsScene *scene;
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *piedra;
    int anchoFondo;
    int anchoCuadrante;

    int desplazamientoHorizontal;
    void adjustBackground();                    //CambioAxel
    MenuInicio *menuInicio;        //CambioAxel  - esto no lo ponga en su codigo de pruebas pero si en el GIT
    Level2 *level2;
    QMenuBar *menuBar;


    int anchoTotalMundo;         //CambioEscena
    int anchoVentana;            //CambioEscena
    void ajustarVistaMundo();    //CambioEscena
    int backgroundWidth;
    int backgroundHeight;

    PerderDialog *perderDialog;
    NivelCompletadoDialog *dialogoNivelCompletado;
    QTimer *timerPosicionJugador;

};

#endif // LEVEL1_H
