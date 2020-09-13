    #include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QStringList psArgs;
    psArgs << "-A";
    ps = new QProcess;
    ps->setProgram("ps");
    ps->setArguments(psArgs);
    ps->setStandardOutputFile("ololo");
    ui->indicateMem->size().setHeight(100);
    ui->indicateMem->size().setWidth(100);

    mem = new QSharedMemory;
    timer = new QTimer();
    timerPong = new QTimer();
    offRed = new QTimer();
    timerTryWrite = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::memIsAvailable);
    connect(offRed, &QTimer::timeout, this, &MainWindow::disableWarning);
    connect(timerTryWrite, &QTimer::timeout, this, &MainWindow::on_pushButton_released);
    connect(timerPong, &QTimer::timeout, this, &MainWindow::friendInvationWaiting);

    timer->start(500);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        ps->start();
        ps->waitForFinished(200);
        psFile = new QFile;
        psFile->setFileName("ololo");
        if(!psFile->open(QFile::ReadOnly | QFile::Text))
            qDebug() << "psFile is not opening.";

        QTextStream psIn(psFile);
        QString psListText = psIn.readAll();
        ps->waitForFinished(200);

        qDebug() << psListText;
        myPid = foundPidByName(psListText, "winpi_lab2_app1");
        friendPid = foundPidByName(psListText, "wiap_lab2_app2");

        if(psListText.contains("wiap_lab2_app2")) {
            ui->label->setText("Found it. My pid is "
                               + myPid
                               + "\n Friends pid is "
                               + friendPid);
            ui->label->setStyleSheet("color: rgb(100, 200, 100);");
        } else {
            emit close();
        }

        QPixmap indGreen(":/img/ind_on.png");
        ui->indicateMem->setPixmap(indGreen);

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
                QPixmap indRed(":/img/ind_red.png");
                ui->indicateMem->setPixmap(indRed);
                offRed->start(2000);
                memStatus = false;
            }
            if(mem->isAttached()) {
                memStatus = true;
                qDebug() << "attached";
            }
        }
    }
}

void MainWindow::on_pushButton_released() {
    QByteArray message = myPid.toUtf8();
    timer->stop();

    if(copyToMem(mem, message + " call me ;)"))
        ui->label->setText("Mesage has sended");
    timer->start(500);
    timerTryWrite->start(70);
}

void MainWindow::friendInvationWaiting() {
        if(copyFromMem(mem, ui).indexOf("Ha-ha-ha XD", 0)) {
            ui->label->setText("friend received a party invitation :3\n");
            timerPong->stop();
            timerTryWrite->stop();
        }
}
//
//    --- Next utils ---
//

bool MainWindow::copyToMem(QSharedMemory *mem, QByteArray msg) {
    char *data = (char*)mem->data();
    if (mem->lock()) {
        for (int i = 0; i < 1024; i++)
            data[i] = ' ';
        for (int i = 0; i < msg.size(); i++)
            data[i] = msg[i];
        timerTryWrite->stop();
     mem->unlock();
    }
    return true;
}

QString MainWindow::copyFromMem(QSharedMemory *mem, Ui::MainWindow *ui) {
    char *data = (char*)mem->data();
    QByteArray mesage;
    if (mem->lock()) {
        for (int i = 0; data[i]; i++)
        mesage.append(data[i]);
     mem->unlock();
    }
    return mesage;
}

QByteArray MainWindow::readFromTo(QByteArray stroke, int beg, int end){  //  ok
    QByteArray readed;
    for(int i = beg; i <= end; i++)
        readed += stroke[i];
    return readed;
}

QString MainWindow::foundPidByName (QString streamText, QString name) {
    QString strWithName;
    int thisAppName = streamText.indexOf(name, 0);
    int thisAppPidEnd = thisAppName + name.length() - 1;
    int thisAppPidBeg = streamText.lastIndexOf("\n", thisAppPidEnd) + 1;
    strWithName = readFromTo(streamText.toUtf8(), thisAppPidBeg, thisAppPidEnd);
    if(strWithName[0] == " ")
        strWithName = readFromTo(strWithName.toUtf8(), 1, strWithName.length());
    thisAppPidEnd = strWithName.indexOf(" ", 0) - 1;

    QString thisAppPid = readFromTo(strWithName.toUtf8(),
                                    0,
                                    thisAppPidEnd);
    qDebug() << thisAppPid;
    return thisAppPid;
}

bool MainWindow::disableWarning() {
    QPixmap indGray(":/img/ind_off.png");
    ui->indicateMem->setPixmap(indGray);
    offRed->stop();
    return true;
}

bool MainWindow::memIsAvailable() {
    qDebug() << "check";
    if(mem->lock()) {
        QPixmap indGreen(":/img/ind_on.png");
        ui->indicateMem->setPixmap(indGreen);
        mem->unlock();
        memStatus = true;
        return true;
    } else {
            QPixmap indRed(":/img/ind_red.png");
            ui->indicateMem->setPixmap(indRed);
            qDebug() << "is not available";
            memStatus = false;
        return false;
    }
}

void MainWindow::on_pushButton_2_released() {
    timerPong->start(400);
}
