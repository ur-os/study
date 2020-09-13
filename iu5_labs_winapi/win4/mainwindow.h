#ifndef SCENE3D_H
#define SCENE3D_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include "text.h"


class MainWindow : public QGLWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    QString *key_buffer;
    text    *worker;
    QThread *thread;

protected:

    int     geese_size; // Размер гуся))
    int     point; // набранные очки
    int     *gdx, *gdy; //wax / 4, gdy = 0; // Координаты объектов (гусей)
    int     cax, cay, cbx, cby; // Координаты курсора
    int     *wax ,*way; // Размеры окна

    void initializeGL(); // Метод для инициализирования opengl
    void resizeGL(int nWidth, int nHeight); // Метод вызываемый после каждого изменения размера окна
    void paintGL(); // Метод для вывода изображения на экран
    void keyPressEvent(QKeyEvent *ke); // Для перехвата нажатия клавиш на клавиатуре
    void singling_lb(); // Рисуем рамку выделенной области
    void geese(); // Рисуем объекты (будущих гусей :) )
    bool renderTextOlolo(QKeyEvent *key);

signals:
    void ololo(QKeyEvent *ke);
protected slots:
    void geese_coord(); // Определяем координаты объектов
};

#endif // SCENE3D_H
