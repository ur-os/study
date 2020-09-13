#ifndef GRAPH_H
#define GRAPH_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>

class graph : public QGLWidget {
    Q_OBJECT
public:
    explicit graph(QWidget *parent = nullptr);
    QString *key_buffer;
    bool toPaintGraph = true;

protected:
    int     wax = 500 ,way = 500, w2x = 250, w2y = 250; // Размеры окуня
    QColor  background;

    struct rgbGl {
        GLfloat r;
        GLfloat g;
        GLfloat b;
    };

    rgbGl   bufferColor, currentColor;

    void initializeGL(); // Метод для инициализирования opengl
    void resizeGL(int nWidth, int nHeight); // Метод вызываемый после каждого изменения размера окна
    void paintGL(); // Метод для вывода изображения на экран
    void keyPressEvent(QKeyEvent *ke); // Для перехвата нажатия клавиш на клавиатуре

    void axis();
    bool renderTextOlolo(QKeyEvent *key);
    void paintLine(int x1,int x2,int y1,int y2, rgbGl color);
    void paintDot(int x,int y, rgbGl color);
    void paintScale(int x_step, int y_step);
    void paintGraph(int scale_x, int scale_y);


protected slots:
    void geese_coord(); // Определяем координаты объектов
    void deleteGraph();

};

#endif // GRAPH_H
