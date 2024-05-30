#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Particula.h"

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

    //FONDO
    QGraphicsScene *scene;
    QGraphicsPixmapItem *fondo;
    int anchoFondo;
    int anchoCuadrante;

    void desplazarFondo(int desplazamiento);
};

#endif // MAINWINDOW_H
