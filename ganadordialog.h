// ganadordialog.h
#ifndef GANADORDIALOG_H
#define GANADORDIALOG_H

#include <QDialog>

class GanadorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GanadorDialog(QWidget *parent = nullptr);
    ~GanadorDialog();

signals:
    void volverMenuPrincipal();

private:
         // Agrega aquí los widgets y miembros necesarios
};

#endif // GANADORDIALOG_H
