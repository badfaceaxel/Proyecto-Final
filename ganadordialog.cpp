// ganadordialog.cpp
#include "ganadordialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

GanadorDialog::GanadorDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("¡Ganaste el juego!");

    QLabel *mensaje = new QLabel("¡Felicidades ganaste el juego!");
    QPushButton *botonVolverMenu = new QPushButton("Volver al Menú");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(mensaje);
    layout->addWidget(botonVolverMenu);

    connect(botonVolverMenu, &QPushButton::clicked, this, &GanadorDialog::volverMenuPrincipal);

    setLayout(layout);
}

GanadorDialog::~GanadorDialog()
{
    // Liberar recursos si es necesario
}
