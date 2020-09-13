#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedMemory>
#include <QBuffer>
#include <QDebug>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QBuffer buffer;
    QDataStream stream;
    QSharedMemory *mem;
    QTimer *timerTryWrite;
    QTimer *timerTryRead;
    QByteArray message = "Ha-ha-ha XD";
    bool memStatus;
    QByteArray readedMem;

    bool tryWriteMem();
    bool tryReadMem();
    QByteArray readFromTo(QByteArray stroke, int beg, int end);

private slots:
    bool memIsAvailable();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
