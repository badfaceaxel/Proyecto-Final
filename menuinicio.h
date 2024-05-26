#ifndef MENUINICIO_H
#define MENUINICIO_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <Qlabel>

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

private:
    Ui::MenuInicio *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *background;
    QGraphicsPixmapItem *titleItem;
    //QLabel *labelTitle;  // Declarar QLabel para el título

    void adjustBackground();
};

#endif // MENUINICIO_H
