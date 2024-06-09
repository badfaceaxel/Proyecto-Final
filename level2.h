#ifndef LEVEL2_H
#define LEVEL2_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QResizeEvent> //CambioAxel
#include <QShowEvent>   //CambioAxel
#include <QTimer>
#include "Enemigo1.h"
#include "Particula.h"
#include "jugador.h"

// Agrega esta línea para la declaración anticipada
class MenuInicio; // Esto le dice al compilador que MenuInicio es una clase       //CambioAxel

namespace Ui {
class Level2;
}

class Level2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Level2(QWidget *parent = nullptr);
    bool clic;
    Jugador *getJugador() { return player; } // Agrega esta función /////////CambioAxel
    ~Level2();

protected:
    void resizeEvent(QResizeEvent *event) override; //CambioAxel
    void showEvent(QShowEvent *event) override;     //CambioAxel

private:
    Ui::Level2 *ui;
    QTimer *timer;
    QList<Enemigo1 *> enemies;
    void crearEnemigos(QGraphicsView *view, Jugador *jugador, QGraphicsScene *scene);

    //FONDO
    QGraphicsScene *scene;
    QGraphicsPixmapItem *background;
    int anchoFondo;
    int anchoCuadrante;

    void desplazarFondo(int desplazamiento);
    void adjustBackground(); //CambioAxel
    MenuInicio *menuInicio; //CambioAxel  - esto no lo ponga en su codigo de pruebas pero si en el GIT

    int anchoTotalMundo;      //CambioEscena
    int anchoVentana;         //CambioEscena
    void ajustarVistaMundo(); //CambioEscena
    int backgroundWidth;
    int backgroundHeight;

    Jugador *player; //CambioAxel
};

#endif // LEVEL2_H
