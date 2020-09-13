#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    timerTryRead = new QTimer;
    timerTryWrite = new QTimer;
    connect(timerTryRead, &QTimer::timeout, this, &MainWindow::tryReadMem);
    connect(timerTryWrite, &QTimer::timeout, this, &MainWindow::tryWriteMem);

    mem = new QSharedMemory;
    mem->setKey("MyKey");
    if(mem->attach()) {
        qDebug() << "mem already exist and attached now";
        memStatus = true;
    } else if(mem->isAttached()) {
        qDebug() << "mem is attached already";
        memStatus = true;
    } else if (mem->create(1024)) {
        if(!mem->attach()) {
            qDebug() << "mem is not created";
            memStatus = false;
        }
        if(mem->isAttached()) {
            memStatus = true;
            qDebug() << "attached";
        }
    }

    char *data = (char*)mem->data();
    if (mem->lock()) {
        for (int i=0; i < 1024; i++)
            data[i] = '\0';
     mem->unlock();
    }

    timerTryRead->start(100);
}

MainWindow::~MainWindow() {
    delete ui;
}

bool MainWindow::tryWriteMem() {
    char *data = (char*)mem->data();
    if (mem->lock()) {
        for (int i = 0; i < 1024; i++)
            data[i] = ' ';
        for (int i=0; i < message.size(); i++)
            data[i] = message[i];
     mem->unlock();
     timerTryWrite->stop();
    }
    return true;
}

bool MainWindow::tryReadMem() {
    char *data = (char*)mem->data();
    QByteArray ar;
    if (mem->lock()) {
        for (int i = 0; data[i]; i++)
        ar.append(data[i]);
     mem->unlock();
    } else {
        return false;
    }
    if(ar.indexOf("call me ;)") != -1) {
        readedMem = ar;
        int beg = 0;
        int end = readedMem.indexOf(" ", 0);
        readedMem = readFromTo(readedMem, beg, end);
        ui->label->setText(readedMem);
        timerTryWrite->start(80);
    }

    return true;
}

bool MainWindow::memIsAvailable() {
    qDebug() << "check";
    if(mem->lock()) {
        mem->unlock();
        memStatus = true;
        return true;
    } else {
        qDebug() << "is not available";
        memStatus = false;
        return false;
    }
}

QByteArray MainWindow::readFromTo(QByteArray stroke, int beg, int end) {  //  ok
    QByteArray readed;
    for(int i = beg; i <= end; i++)
        readed += stroke[i];
    return readed;
}
