#include <QRandomGenerator>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <QDebug>
#include <QTimer>

#include "mainwindow.h"
#include "glwidget.h"



GLWidget::GLWidget(QWidget *parent) :
    QGLWidget (parent) {
}

void GLWidget::initializeGL() {
    glClearColor(1, 1, 0, 1);
    setMouseTracking(true);
    glLoadIdentity();
    glOrtho(0, 806, 532, 0, 0, 1);

}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);

}

void GLWidget::paintGL() {
    glClearColor(0.7, 0, 0.5, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);

    glPaintLab1_17();

}

void GLWidget::glPaintLab1_17() {
        generateSquare(0, 300);
}

void GLWidget::generateSquare(int x, int size) {
    glColor3d(colorsSet->kingSize->red,
              colorsSet->kingSize->green,
              colorsSet->kingSize->blue);
    glBegin(GL_POLYGON);
        glVertex2d(x, x);
        glVertex2d(x, size);
        glVertex2d(size, size);
        glVertex2d(size, x);
    glEnd();

    glColor3d(colorsSet->medium->red,
              colorsSet->medium->green,
              colorsSet->medium->blue);
    glBegin(GL_POLYGON);
        glVertex2d(x, x);
        glVertex2d(x, size - 50);
        glVertex2d(size - 50, size - 50);
        glVertex2d(size - 50, x);
    glEnd();

    glColor3d(colorsSet->small->red,
              colorsSet->small->green,
              colorsSet->small->blue);
    glBegin(GL_POLYGON);
        glVertex2d(x, x);
        glVertex2d(x, size - 100);
        glVertex2d(size - 100, size - 100);
        glVertex2d(size - 100, x);
    glEnd();
    glFlush();
}

void GLWidget::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        xAtPress = event->x();
        yAtPress = event->y();
        qDebug() << xAtPress << " " <<yAtPress ;
        if(xAtPress < 201 && yAtPress < 201) {
            colorsSet->swapColors(colorsSet->small, colorsSet->medium);
            generateSquare(0, 300);
            updateGL();
        } else {
            if(xAtPress < 251 && yAtPress < 251) {
                colorsSet->swapColors(colorsSet->kingSize, colorsSet->medium);
                generateSquare(0, 300);
                updateGL();
            } else {
                if(xAtPress < 301 && yAtPress < 301) {
                    colorsSet->swapColors(colorsSet->small, colorsSet->kingSize);
                    generateSquare(0, 300);
                    updateGL();
                }
            }
        }
    }
    if(event->button() == Qt::RightButton) {
        QTimer* timer = new QTimer;
        connect(timer, SIGNAL(timeout()), this, SLOT(escape()));
        timer->start(15000);
    }

}

void GLWidget::escape() {
    emit destroyed();
}
