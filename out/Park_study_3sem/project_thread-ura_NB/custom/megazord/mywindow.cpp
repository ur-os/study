#include <QDebug>
#include <QKeyEvent>
#include <Qt3DRender>
#include <QThread>
#include "cube.h"
#include "frame.h"
#include "utils.h"
#include "mywindow.h"
#include "frame.h"
#include "workerthread.h"

MyWindow::MyWindow(QScreen *screen):Qt3DExtras::Qt3DWindow(screen) {

    defaultFrameGraph()->setClearColor(QColor(246,246,246));
    WorkerThread thread("/home/byeti/project/custom/megazord/rat_lab");

    QVector <QVector <QVector <Qube>>> array2;

    GdbInterface mana("/home/byeti/project/custom/megazord/rat_lab");
    mana.gdb.start();
    mana.trigger();

    if(!mana.magicEssence.isEmpty())
        array2 = mana.magicEssence;
    else
        array2.push_back(mana.empty2);

    createEntity(array2);
    this->setRootEntity(root);

    camera()->lens()->setPerspectiveProjection(40.0f,static_cast<float>(this->width()/this->height()),0.1f,1000.0f);
    camera()->setPosition(QVector3D(60.0f, 60.0f, 60.0f));
    camera()->setViewCenter(QVector3D(-15.0f, 0.0f, 0.0f));

    this->set_camera(root);

    Qt3DCore::QEntity *lightEntity = new Qt3DCore::QEntity(root);
    Qt3DRender::QDirectionalLight *directionalLight1 = new Qt3DRender::QDirectionalLight(lightEntity);
    Qt3DRender::QDirectionalLight *directionalLight3 = new Qt3DRender::QDirectionalLight(lightEntity);
    Qt3DRender::QDirectionalLight *directionalLight4 = new Qt3DRender::QDirectionalLight(lightEntity);

    directionalLight1->setWorldDirection(QVector3D(50.0f, 50.0f, -100.0f));
    directionalLight3->setWorldDirection(QVector3D(-50.0f, -50.0f, -100.0f));
    directionalLight4->setWorldDirection(QVector3D(-50.0f, -50.0f, 100.0f));

    lightEntity->addComponent(directionalLight1);
    lightEntity->addComponent(directionalLight3);
    lightEntity->addComponent(directionalLight4);

}

MyWindow::~MyWindow() {

}

void MyWindow::keyPressEvent(QKeyEvent *ev) {
    switch (ev->key()) {
        case Qt::Key_W:
            camera()->setPosition(QVector3D(60.0f, 60.0f, 60.0f));
            camera()->setUpVector(QVector3D(0.0f, 50.0f, 0.0f));
            camera()->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

            break;
        case Qt::Key_E:{
            auto rootEntity = new Qt3DCore::QEntity;
            auto f = new Frame (rootEntity);

            f->set_Y(rootEntity, -30);
            f->set_width(60);
            f->print_text("array2[k][i-1][j-1].scope");

            this->set_camera(rootEntity);
            setRootEntity(rootEntity);
//            set_camera(rootEntity);
//            auto r = root;
            //root = rootEntity;
//            delete r;
            break;}
        case Qt::Key_U:
        if(isUpdated) {
            isUpdated = false;

        }
            break;
        default:
            break;
    }
}

void MyWindow::set_camera(Qt3DCore::QEntity *scene) {

    cameraController = new Qt3DExtras::QOrbitCameraController(scene);
    cameraController->setCamera(camera());
    cameraController->setLookSpeed(100.0f);
    cameraController->setLinearSpeed(50.0f);
    cameraController->setZoomInLimit(50.0f);

}

void MyWindow::createEntity(QVector <QVector <QVector <Qube>>>& array) {
    auto rootEntity = new Qt3DCore::QEntity;
    root = rootEntity;

    Cube* c;
    Qube* q;
    Frame* f;
    float y = 0;
    float z = 0;
    float FramePos = 0;
    float FramePosOld = 0;
    int i, j, k;
    y = 0;
    z = 0;
    FramePos = 0;
    FramePosOld = 0;

    for (k = 0; k <array.size(); k++ ) {
        for (i = 0; i < array.at(k).size(); i++) {
            y -= 20.0f;
            FramePos -= 20.0f;
            z = -4.98f;
            for (j = 0; j < array.at(k).at(i).size(); j++) {
                z += 10.0f;
                q = &array[k][i][j];
                c = new Cube(rootEntity, q);
                c->createObjectPicker(this);
                c->print_text();
                c->y = y;
                c->z = z;
               c->set_YZ(rootEntity);

            }
        }
        FramePos -= 20.0f;
        y -= 20.0f;
        f = new Frame (rootEntity);
        f->set_Y(rootEntity, (FramePos-FramePosOld)/2+FramePosOld);
        f->set_width(-FramePos + FramePosOld);
        f->print_text(array[k][i-1][j-1].scope);
        FramePosOld = FramePos;
   }
}

void MyWindow::applyHotSwapEntity(/*here entity*/) {
    root = rootEntity;
}
