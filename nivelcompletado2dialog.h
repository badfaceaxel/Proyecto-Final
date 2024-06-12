// nivelcompletadodialog.h
#ifndef NIVELCOMPLETADO2DIALOG_H
#define NIVELCOMPLETADO2DIALOG_H

#include <QDialog>

class NivelCompletado2Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit NivelCompletado2Dialog(QWidget *parent = nullptr);
    ~NivelCompletado2Dialog();

signals:
    void continuarNivel3();
    void volverMenuPrincipal();

private:
         // Agrega aquí los widgets y miembros necesarios
};

#endif // NIVELCOMPLETADO2DIALOG_H
