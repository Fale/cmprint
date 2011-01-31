#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
   // w.resize(800,600);
   // w.setMinimumHeight(700);
    w.show();
    //w.showMaximized();
    return a.exec();
        qDebug() << QFileDialog::getOpenFileName();
}
