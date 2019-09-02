#include "mainwindow.h"
#include <QApplication>
#include <QVariant>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //MyUDP server;

    w.SeyHello();
    return a.exec();
}
