#include "nivelselecciondialog.h"

NivelSeleccionDialog::NivelSeleccionDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Seleccione el nivel");

    QVBoxLayout *layout = new QVBoxLayout(this);

    nivel1Button = new QPushButton("Nivel 1", this);
    connect(nivel1Button, &QPushButton::clicked, this, &NivelSeleccionDialog::on_nivel1Button_clicked);
    layout->addWidget(nivel1Button);

    nivel2Button = new QPushButton("Nivel 2", this);
    connect(nivel2Button, &QPushButton::clicked, this, &NivelSeleccionDialog::on_nivel2Button_clicked);
    layout->addWidget(nivel2Button);

    nivel3Button = new QPushButton("Nivel 3", this);
    connect(nivel3Button, &QPushButton::clicked, this, &NivelSeleccionDialog::on_nivel3Button_clicked);
    layout->addWidget(nivel3Button);

    setLayout(layout);
}

void NivelSeleccionDialog::on_nivel1Button_clicked()
{
    emit nivelSeleccionado(1);
    accept(); // Cierra el diálogo después de seleccionar el nivel
}

void NivelSeleccionDialog::on_nivel2Button_clicked()
{
    emit nivelSeleccionado(2);
    accept(); // Cierra el diálogo después de seleccionar el nivel
}

void NivelSeleccionDialog::on_nivel3Button_clicked()
{
    emit nivelSeleccionado(3);
    accept(); // Cierra el diálogo después de seleccionar el nivel
}
