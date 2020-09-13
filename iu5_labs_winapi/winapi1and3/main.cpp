#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette p;
    p = qApp->palette();
    p.setColor(QPalette::Window, QColor(53,53,53));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::Highlight, QColor(245, 0, 87));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    p.setColor(QPalette::Background, QColor(53,53,53));
    qApp->setPalette(p);
    MainWindow w;
    w.show();

    return a.exec();
}
