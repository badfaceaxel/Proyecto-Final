#include "mainwindow.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (argc < 2) {
        qDebug() << "Error: No se pasó ningún argumento";
        return -1;
    }
    int salto = std::atoi(argv[1]);
    qDebug() << salto;

    MainWindow w(salto);
    w.show();
    return a.exec();
}
