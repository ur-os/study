#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QEvent>
#include <QProcess>
#include <QTextStream>
#include <QDebug>
#include <QSharedMemory>
#include <QBuffer>
#include <QTimer>
#include <QPixmap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QProcess *ps;
    QFile *psFile;
    QTimer *timer;
    QTimer *offRed;
    QTimer *timerPong;
    QTimer *timerTryWrite;
    QString myPid;
    QString friendPid;

    QBuffer buffer;
    QDataStream stream;
    QSharedMemory *mem;
    QPixmap gray, green, red;
    bool trySendMessage;
    bool memStatus = false;

    void mouseReleaseEvent(QMouseEvent *ev);
    QString foundPidByName (QString stream, QString name);
    QByteArray readFromTo(QByteArray stroke, int beg, int end);
    bool copyToMem(QSharedMemory *mem, QByteArray msg);
    QString copyFromMem(QSharedMemory *mem, Ui::MainWindow *ui);

private slots:
    bool memIsAvailable();
    void on_pushButton_released();
    bool disableWarning();
    void friendInvationWaiting();

    void on_pushButton_2_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
