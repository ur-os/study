#include "graph.h"
#include <math.h>

graph::graph(QWidget *parent) : QGLWidget(parent) {
    wax = 500; way = 500; // начальный размер окна
    background.setRgb(40, 40, 40, 255);
    currentColor = {0.3, 0.8, 0.3};

    key_buffer = new QString;

    updateGL();
    setFormat(QGLFormat(QGL::DoubleBuffer)); // Двойная буферизация
    glDepthFunc(GL_LEQUAL); // Буфер глубины
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &graph::geese_coord);
    timer->start(40);
}

void graph::initializeGL() {
    qglClearColor(background);
}

void graph::resizeGL(int nWidth, int nHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    wax = nWidth;
    w2x = wax / 2;
    way = nHeight;
    w2y = way / 2;
}

void graph::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity(); // загружаем матрицу
    glOrtho(0, wax, way, 0, 1, 0); // подготавливаем плоскости для матрицы
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    paintScale(10, 10);
    if (toPaintGraph)
        paintGraph(wax / 500, way/ 500);
    axis();

    swapBuffers();
}

void graph::keyPressEvent(QKeyEvent *keyboard) {
    qDebug() << keyboard->text();
}

void graph::axis() {
    paintLine(wax / 2, 0, wax / 2, way, currentColor);
    paintLine(0, way / 2, wax, way / 2, currentColor);

    paintLine(wax,          w2y,
              wax * 0.98,   w2y * 0.99, currentColor);
    paintLine(wax,          w2y,
              wax * 0.98,   w2y * 1.01, currentColor);

    paintLine(w2x,          0,
              w2x * 0.99,   way * 0.02, currentColor);
    paintLine(w2x,          0,
              w2x * 1.01,   way * 0.02, currentColor);

    renderText(wax - 15,    w2y + 15,      0, "x", QFont());
    renderText(w2x + 15,    15,            0, "y", QFont());
    renderText(w2x - 15,    w2y + 15,      0, "0", QFont());

}

void graph::paintLine(int x1,int y1,int x2,int y2, rgbGl color) {
    glBegin(GL_LINES);
        glColor3f(color.r, color.g, color.b);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
    glEnd();
}

void graph::paintDot(int x, int y, graph::rgbGl color) {
    glBegin(GL_POINTS);
        glColor3f(color.r, color.g, color.b);
        glVertex2d(x, y);
        glColor3f(color.r / 2, color.g / 2, color.b / 2);
        glVertex2d(x, y + 1);
        glVertex2d(x, y - 1);
        glColor3f(color.r / 4, color.g / 4, color.b / 4);
        glVertex2d(x, y + 2);
        glVertex2d(x, y - 2);
    glEnd();
}



void graph::paintScale(int x_step, int y_step) {


    bufferColor = currentColor;
    currentColor = {0.25, 0.25, 0.25};
        //  x
    for(int i = 0; i < w2x / x_step; i ++) {
        paintLine(x_step * i + w2x, 5,
                  x_step * i + w2x, way - 5, currentColor);
    }
    for(int i = 0; i < w2x / x_step; i ++) {
        paintLine(w2x - x_step * i, 5,
                  w2x - x_step * i, way - 5, currentColor);
    }
        //  y
    for(int i = 0; i < w2y / y_step; i ++) {
        paintLine(5     , y_step * i + w2y,
                  wax - 5   , y_step * i + w2y, currentColor);
    }
    for(int i = 0; i < w2y / y_step; i ++) {
        paintLine(5     , w2y - y_step * i,
                  wax - 5   , w2y - y_step * i, currentColor);
    }


    currentColor = bufferColor;
    bufferColor = {0, 0, 0};
}

void graph::geese_coord() {
    updateGL();
}

void graph::deleteGraph() {
    toPaintGraph = false;
    updateGL();
}

void graph::paintGraph(int scale_x, int scale_y) {
    bufferColor = currentColor;
    currentColor = {0.2, 0.8, 0.2};

    float t = -77;
    for(int i = -770 * 5; i <= 770 * 5; i++) {
        paintDot( ((5.4 * cos(t)) + (5 * cos(5.4 / 2.3 * t))) * scale_x * 3 + w2x,
                  ((5.4 * sin(t)) + (51 * sin(5.4 / 2.3 * t)))* scale_y * 3 + w2y, currentColor);
        t += 0.02;
    }


    currentColor = bufferColor;
    bufferColor = {0,0,0};
}
