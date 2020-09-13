#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSharedMemory>
#include <QSystemSemaphore>
#include <QMouseEvent>

#include "glwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
    void on_textEdit_textChanged();
    void on_comboBox_highlighted(int index);
    void on_comboBox_2_highlighted(int index);
    void on_checkBox_released();
    void on_checkBox_2_released();
    void on_pushButton_3_released();

private:
    Ui::MainWindow *ui;
    GLWidget widget;

};

#endif // MAINWINDOW_H
