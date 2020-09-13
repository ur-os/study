#include "workerthread.h"

//WorkerThread::WorkerThread(QByteArray pathToProg) {
//    GdbInterface mana(pathToProg);
//    mana.gdb.startDetached(&mana.pid);
//    mana.gdb.waitForStarted();
//    connect(this, &WorkerThread::giveMeArray2, &mana, &GdbInterface::trigger);
//    connect(&mana, &GdbInterface::parsed, this, &WorkerThread::makeMeEntity);
//}

//void WorkerThread::needUpdate() {
//    run();
//}

//void WorkerThread::run() {

//}

//void WorkerThread::makeMeEntity(QVector <QVector <QVector <Qube>>> array) {
//    auto rootEntity = new Qt3DCore::QEntity;
////    root = rootEntity;

//    Cube* c;
//    Qube* q;
//    Frame* f;
//    float y = 0;
//    float z = 0;
//    float FramePos = 0;
//    float FramePosOld = 0;
//    int i, j, k;
//    y = 0;
//    z = 0;
//    FramePos = 0;
//    FramePosOld = 0;

//    for (k = 0; k <array.size(); k++ ) {
//        for (i = 0; i < array.at(k).size(); i++) {
//            y -= 20.0f;
//            FramePos -= 20.0f;
//            z = -4.98f;
//            for (j = 0; j < array.at(k).at(i).size(); j++) {
//                z += 10.0f;
//                q = &array[k][i][j];
//                c = new Cube(rootEntity, q);
//                //c->createObjectPicker(this);
//                c->print_text();
//                c->y = y;
//                c->z = z;
//               c->set_YZ(rootEntity);

//            }
//        }
//        FramePos -= 20.0f;
//        y -= 20.0f;
//        f = new Frame (rootEntity);
//        f->set_Y(rootEntity, (FramePos-FramePosOld)/2+FramePosOld);
//        f->set_width(-FramePos + FramePosOld);
//        f->print_text(array[k][i-1][j-1].scope);
//        FramePosOld = FramePos;
//    }
//    emit updatedEntity(rootEntity);
//}

