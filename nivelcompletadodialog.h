// nivelcompletadodialog.h
#ifndef NIVELCOMPLETADODIALOG_H
#define NIVELCOMPLETADODIALOG_H

#include <QDialog>

class NivelCompletadoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NivelCompletadoDialog(QWidget *parent = nullptr);
    ~NivelCompletadoDialog();

signals:
    void continuarNivel2();
    void continuarNivel3();
    void volverMenuPrincipal();

private:
         // Agrega aquí los widgets y miembros necesarios
};

#endif // NIVELCOMPLETADODIALOG_H
