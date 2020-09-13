#include "mainwindow.h"


MainWindow::MainWindow(QWidget* parent) : QGLWidget(parent) {
    point = 0;
    geese_size = 30;
    wax = new int;
    way = new int;
    *wax = 500; *way = 500; // начальный размер окна

    gdx = new int;
    gdy = new int;
    *gdx = *wax / 4; *gdy = 0;

    key_buffer = new QString;

    geese_coord();
    setFormat(QGLFormat(QGL::DoubleBuffer)); // Двойная буферизация
    glDepthFunc(GL_LEQUAL); // Буфер глубины
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(geese_coord()));
    timer->start(40);

    worker = new text(gdx, gdy, wax, way);
    thread = new QThread;
    worker->moveToThread(thread);
    thread->start();

}

void MainWindow::initializeGL() {
    qglClearColor(Qt::darkGray);
}

void MainWindow::resizeGL(int nWidth, int nHeight) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    *wax = nWidth;
    *way = nHeight;
}

void MainWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим буфер изображения и буфер глубины
    glMatrixMode(GL_PROJECTION); // устанавливаем матрицу
    glLoadIdentity(); // загружаем матрицу
    glOrtho(0, *wax, *way, 0, 1, 0); // подготавливаем плоскости для матрицы
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    renderText(*wax / 2, 20 , 0, *key_buffer, QFont());

    geese();

    swapBuffers();
}

void MainWindow::keyPressEvent(QKeyEvent *keyboard) {
    if(keyboard->text() == '\b')    key_buffer->remove(key_buffer->length() - 1, 1);
        else                        key_buffer->push_back(keyboard->text());


    qDebug() << *key_buffer;
}

void MainWindow::geese_coord() {
    updateGL();
}


void MainWindow::geese() {
    glBegin(GL_POLYGON);
        glColor3f(0.32, 0.3, 0.3);
        // Координаты выделенной области
        glVertex2f(*gdx, *gdy);
        glVertex2f(*gdx + geese_size, *gdy);
        glVertex2f(*gdx + geese_size, *gdy + geese_size);
        glVertex2f(*gdx, *gdy + geese_size);
    glEnd();
}
