#include "perderdialog.h"

PerderDialog::PerderDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    volverMenuButton = new QPushButton(tr("Volver al menú"), this);
    reiniciarNivelButton = new QPushButton(tr("Reiniciar nivel"), this);

    layout->addWidget(volverMenuButton);
    layout->addWidget(reiniciarNivelButton);

    connect(volverMenuButton, &QPushButton::clicked, this, &PerderDialog::on_volverMenuButton_clicked);
    connect(reiniciarNivelButton, &QPushButton::clicked, this, &PerderDialog::on_reiniciarNivelButton_clicked);
}

void PerderDialog::on_volverMenuButton_clicked()
{
    emit volverMenu();
    accept();
}

void PerderDialog::on_reiniciarNivelButton_clicked()
{
    emit reiniciarNivel();
    accept();
}
