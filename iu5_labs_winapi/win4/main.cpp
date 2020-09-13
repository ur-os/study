#include <QtGui>
#include "mainwindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow window;
    window.setGeometry(200,200,500,500); // Смещение и положение окна
    window.show();

    return app.exec();
}
