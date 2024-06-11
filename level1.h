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


// Agrega esta línea para la declaración anticipada
class MenuInicio;  // Esto le dice al compilador que MenuInicio es una clase       //CambioAxel


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

protected:
    void resizeEvent(QResizeEvent *event) override;    //CambioAxel
    void showEvent(QShowEvent *event) override;        //CambioAxel

private slots:
    //void actualizarCorazones(int nuevaVida);


private:
    Ui::Level1 *ui;
    QTimer *timer;
    QList<Enemigo1*> enemies;
    QVector<Enemigo2*> enemies2;
    void crearEnemigos(QGraphicsView* view, Jugador* jugador, QGraphicsScene* scene);
    void crearEnemigos2(QGraphicsView* view, Jugador* jugador, QGraphicsScene* scene);

    Jugador *player;   //CambioAxel
    //QVector<QGraphicsPixmapItem*> corazones;


    //FONDO
    QGraphicsScene *scene;
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *piedra;
    int anchoFondo;
    int anchoCuadrante;

    void desplazarFondo(int desplazamiento);
    void adjustBackground();                    //CambioAxel
    MenuInicio *menuInicio;        //CambioAxel  - esto no lo ponga en su codigo de pruebas pero si en el GIT
    QMenuBar *menuBar;


    int anchoTotalMundo;         //CambioEscena
    int anchoVentana;            //CambioEscena
    void ajustarVistaMundo();    //CambioEscena
    int backgroundWidth;
    int backgroundHeight;
};

#endif // LEVEL1_H
