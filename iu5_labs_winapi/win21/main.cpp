#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QPalette>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Fallout Shelter");
    qApp->setStyle(QStyleFactory::create("Fusion"));
    w.show();

    return a.exec();
}
