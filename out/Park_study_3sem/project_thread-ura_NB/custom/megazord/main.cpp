#include <QGuiApplication>
#include <QApplication>
#include <Qt3DExtras>
#include <Qt3DCore>
#include <Qt3DRender>

#include <QtDebug>
#include <QMap>
#include <QText2DEntity>

#include "mywindow.h"
#include "cube.h"
#include "frame.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    MyWindow *view = new MyWindow();
    QThread gdbThread;

    view->show();
    app.exec();
    return 0;
}
