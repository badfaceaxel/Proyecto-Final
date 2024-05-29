#ifndef MENUINICIO_H
#define MENUINICIO_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QEvent>
#include <QResizeEvent>
#include <QShowEvent>
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class MenuInicio;
}
QT_END_NAMESPACE

class MenuInicio : public QMainWindow
{
    Q_OBJECT

public:
    MenuInicio(QWidget *parent = nullptr);
    ~MenuInicio();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override; // Agregar showEvent
    bool eventFilter(QObject *obj, QEvent *event) override;  // Agrega esta línea

private slots:
    void onBotonInicioClicked();
    void onBotonScoreClicked();
    void onBotonSalirClicked();

private:
    Ui::MenuInicio *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *titleItem;
    QGraphicsPixmapItem *signItem;
    QPushButton *botonInicio;
    QPushButton *botonScore;
    QPushButton *botonSalir;
    QPixmap botonInicioNormal;
    QPixmap botonInicioRojo;
    QPixmap botonScoreNormal;
    QPixmap botonScoreRojo;
    QPixmap botonSalirNormal;
    QPixmap botonSalirRojo;
    QSoundEffect* hoverSound;
    QSoundEffect* clickSound;

    void adjustBackground();
    void adjustButtons();
    void adjustSign();
};
#endif // MENUINICIO_H
