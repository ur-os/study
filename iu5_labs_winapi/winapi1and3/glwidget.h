#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QMouseEvent>
#include <GL/glut.h>

#include "squarelab1.h"

class GLWidget : public QGLWidget {
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void mousePressEvent(QMouseEvent* event);

    SquareLab1* colorsSet = new SquareLab1;
    void generateSquare(int x, int size);
    void glPaintLab1_17();

private:
    int xAtPress = 0, yAtPress = 0;
private slots:
    void escape();
};

#endif // GLWIDGET_H
