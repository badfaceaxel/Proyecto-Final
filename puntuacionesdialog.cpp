#include "puntuacionesdialog.h"
#include <QFile>
#include <QTextStream>
#include <QLayout>

PuntuacionesDialog::PuntuacionesDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Tabla de Puntuaciones");
    resize(600, 400);

    tablaScores = new QTableWidget(this);
    tablaScores->setColumnCount(3);
    tablaScores->setHorizontalHeaderLabels(QStringList() << "#" << "Nickname" << "Puntuación");
    tablaScores->setColumnWidth(0, 100); // Ajusta el ancho de la columna "#"
    tablaScores->setColumnWidth(1, 300); // Ajusta el ancho de la columna "Nickname"
    tablaScores->setColumnWidth(2, 200); // Ajusta el ancho de la columna "Puntuación"

    cargarDatos();
    ordenarPorPuntuacion();

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(tablaScores);
    setLayout(layout);
}

void PuntuacionesDialog::cargarDatos() {
    QFile archivo("datos.csv");
    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&archivo);
        int fila = 0;
        while (!in.atEnd()) {
            QString linea = in.readLine();
            QStringList campos = linea.split(",");
            if (campos.size() == 2) {
                QString nickname = campos[0];
                int puntuacion = campos[1].toInt();
                tablaScores->insertRow(fila);
                tablaScores->setItem(fila, 0, new QTableWidgetItem(QString::number(fila + 1)));
                tablaScores->setItem(fila, 1, new QTableWidgetItem(nickname));
                tablaScores->setItem(fila, 2, new QTableWidgetItem(QString::number(puntuacion)));
                fila++;
            }
        }
        archivo.close();
    }
}

void PuntuacionesDialog::ordenarPorPuntuacion() {
    tablaScores->sortItems(2, Qt::DescendingOrder);
}
