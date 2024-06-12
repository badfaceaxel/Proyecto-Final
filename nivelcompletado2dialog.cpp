// nivelcompletadodialog.cpp
#include "nivelcompletado2dialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

NivelCompletado2Dialog::NivelCompletado2Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("¡Nivel 2 completado!");

    QLabel *mensaje = new QLabel("¡Completaste el segundo nivel!");
    QPushButton *botonContinuar = new QPushButton("Continuar al Nivel 3");
    QPushButton *botonVolverMenu = new QPushButton("Volver al Menú");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(mensaje);
    layout->addWidget(botonContinuar);
    layout->addWidget(botonVolverMenu);

    connect(botonContinuar, &QPushButton::clicked, this, &NivelCompletado2Dialog::continuarNivel3);
    connect(botonVolverMenu, &QPushButton::clicked, this, &NivelCompletado2Dialog::volverMenuPrincipal);

    setLayout(layout);
}

NivelCompletado2Dialog::~NivelCompletado2Dialog()
{
    // Liberar recursos si es necesario
}
