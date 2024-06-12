#ifndef PUNTUACIONESDIALOG_H
#define PUNTUACIONESDIALOG_H

#include <QDialog>
#include <QTableWidget>

class PuntuacionesDialog : public QDialog {
    Q_OBJECT

public:
    PuntuacionesDialog(QWidget* parent = nullptr);

private:
    QTableWidget* tablaScores;

    void cargarDatos();
    void ordenarPorPuntuacion();
};

#endif // PUNTUACIONESDIALOG_H
