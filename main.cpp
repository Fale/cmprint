#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   //w.resize(800,600);
   // w.setMinimumHeight(700);
    //w.show();
    //w.setMaximumHeight(600);
    //w.setMaximumWidth(1024);
    w.showMaximized();
    return a.exec();
}
