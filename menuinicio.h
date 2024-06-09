#ifndef MENUINICIO_H
#define MENUINICIO_H

#include <QApplication>
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
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QComboBox>

// Agrega esta línea para la declaración anticipada
class Level1;  // Esto le dice al compilador que Level1 es una clase, sin dar detalles
class Level2;  // Esto le dice al compilador que Level1 es una clase, sin dar detalles
class Level3;  // Esto le dice al compilador que Level1 es una clase, sin dar detalles
class Jugador;
class nicknamedialog;
class nivelselecciondialog;


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


public slots:



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
    QSoundEffect* music;

    Level1 *level1;
    Level2 *level2;
    Level3 *level3;




    void adjustBackground();
    void adjustButtons();
    void adjustSign();

signals:

};
#endif // MENUINICIO_H
