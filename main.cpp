#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   // w.setFixedHeight(700);
    w.showMaximized();
   // w.show();

    return a.exec();
}
