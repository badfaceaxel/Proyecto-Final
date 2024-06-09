#ifndef LEVEL3_H
#define LEVEL3_H

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
class Level3;
}

class Level3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit Level3(QWidget *parent = nullptr);
    bool clic;
    Jugador *getJugador() { return player; } // Agrega esta función /////////CambioAxel
    ~Level3();

protected:
    void resizeEvent(QResizeEvent *event) override; //CambioAxel
    void showEvent(QShowEvent *event) override;     //CambioAxel

private:
    Ui::Level3 *ui;
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

#endif // LEVEL3_H
