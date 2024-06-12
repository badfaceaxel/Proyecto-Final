#ifndef PERDERDIALOG_H
#define PERDERDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

class PerderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PerderDialog(QWidget *parent = nullptr);

signals:
    void volverMenu();
    void reiniciarNivel();

private slots:
    void on_volverMenuButton_clicked();
    void on_reiniciarNivelButton_clicked();

private:
    QPushButton *volverMenuButton;
    QPushButton *reiniciarNivelButton;
};

#endif // PERDERDIALOG_H
