#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Particula.h"
#include "Enemigo1.h"
#include "Enemigo2.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool clic;

private slots:


private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QList<Enemigo1*> enemies;
    QVector<Enemigo2*> enemies2;
    void crearEnemigos(QGraphicsView* view, Jugador* jugador, QGraphicsScene* scene);
    void crearEnemigos2(QGraphicsView* view, Jugador* jugador, QGraphicsScene* scene);

    //FONDO
    QGraphicsScene *scene;
    QGraphicsPixmapItem *fondo;
    int anchoFondo;
    int anchoCuadrante;

    int m_salto;

};

#endif // MAINWINDOW_H
