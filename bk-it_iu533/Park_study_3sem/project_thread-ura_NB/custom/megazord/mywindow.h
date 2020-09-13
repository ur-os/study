#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <Qt3DExtras>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DCore>
#include <QMouseEvent>
#include "utils.h"

class MyWindow: public Qt3DExtras::Qt3DWindow {
    Q_OBJECT
    Qt3DExtras::QOrbitCameraController *cameraController;

public:
    Qt3DCore::QEntity *root;

    bool isUpdated = true;

    MyWindow(QScreen *screen = nullptr);
    ~MyWindow();
    void set_camera(Qt3DCore::QEntity *scene);

public slots:
    void createEntity(QVector <QVector <QVector <Qube>>>& array);
    void applyHotSwapEntity(/*here entity*/);

signals:
    void updatePls();  //  to needUpdate() (thread)

protected:
    void keyPressEvent(QKeyEvent *ev);
};

#endif // MYWINDOW_H
