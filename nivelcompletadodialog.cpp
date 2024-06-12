// nivelcompletadodialog.cpp
#include "nivelcompletadodialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

NivelCompletadoDialog::NivelCompletadoDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("¡Nivel completado!");

    QLabel *mensaje = new QLabel("¡Completaste el primer nivel!");
    QPushButton *botonContinuar = new QPushButton("Continuar al Nivel 2");
    QPushButton *botonVolverMenu = new QPushButton("Volver al Menú");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(mensaje);
    layout->addWidget(botonContinuar);
    layout->addWidget(botonVolverMenu);

    connect(botonContinuar, &QPushButton::clicked, this, &NivelCompletadoDialog::continuarNivel2);
    connect(botonContinuar, &QPushButton::clicked, this, &NivelCompletadoDialog::continuarNivel3);
    connect(botonVolverMenu, &QPushButton::clicked, this, &NivelCompletadoDialog::volverMenuPrincipal);

    setLayout(layout);
}

NivelCompletadoDialog::~NivelCompletadoDialog()
{
    // Liberar recursos si es necesario
}
