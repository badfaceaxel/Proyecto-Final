#ifndef NIVELSELECCIONDIALOG_H
#define NIVELSELECCIONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>

class NivelSeleccionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NivelSeleccionDialog(QWidget *parent = nullptr);
    void on_nivel1Button_clicked();
    void on_nivel2Button_clicked();
    void on_nivel3Button_clicked();

signals:
    void nivelSeleccionado(int nivel);

private:
    QPushButton *nivel1Button;
    QPushButton *nivel2Button;
    QPushButton *nivel3Button;
};

#endif // NIVELSELECCIONDIALOG_H
