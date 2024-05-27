#ifndef MENUINICIO_H
#define MENUINICIO_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <Qlabel>
#include <QPushButton>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MenuInicio; }
QT_END_NAMESPACE

class MenuInicio : public QWidget
{
    Q_OBJECT

public:
    explicit MenuInicio(QWidget *parent = nullptr);
    ~MenuInicio();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent *event) override; // Agregar showEvent

private slots:
    void onBotonInicioClicked();
    void onBotonScoreClicked();
    void onBotonSalirClicked();

private:
    Ui::MenuInicio *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *titleItem;
    QPushButton *botonInicio;
    QPushButton *botonScore;
    QPushButton *botonSalir;
    //QLabel *labelTitle;  // Declarar QLabel para el título

    void adjustBackground();
    void adjustButtons();
};

#endif // MENUINICIO_H
