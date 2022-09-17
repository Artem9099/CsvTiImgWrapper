#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMinimized();
    w.close();
//    qApp->closeAllWindows();
//    qApp->quit();
    QApplication::closeAllWindows();
    QApplication::quit();
    QCoreApplication::quit();
    QCoreApplication::exit();
    //return a.exec();
    return 0;
}
