#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

//#include <QThread>
//#include "utils.h"
//#include <QDebug>
//#include <QKeyEvent>
//#include <Qt3DRender>
//#include <QThread>

//#include "cube.h"
//#include "frame.h"
//#include "utils.h"
//#include "mywindow.h"
//#include "frame.h"

//class WorkerThread : public QThread {
//    Q_OBJECT
//    void run() override;

//public:
//    WorkerThread(QByteArray pathToProg);

//public slots:
//    void needUpdate();  //  send giveMeArray2() to gdbInterface
//    void makeMeEntity(QVector <QVector <QVector <Qube>>> magicEssence);

//signals:
//    void giveMeArray2();
//    void resultReady(const QString &s);
//    void updatedEntity(Qt3DCore::QEntity *entity);
//};

//void MyObject::startWorkInAThread() {
//    WorkerThread *workerThread = new WorkerThread(this);
//    connect(workerThread, &WorkerThread::resultReady, this, &MyObject::handleResults);
//    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
//    workerThread->start();
//}

#endif // WORKERTHREAD_H
