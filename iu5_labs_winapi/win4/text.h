#ifndef TEXT_H
#define TEXT_H

#include <QThread>
#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>
#include <QWidget>


class text : public QThread {
    Q_OBJECT
public:
    int *gdx_local, *gdy_local, *wax_local, *way_local;
    text(int *gdx, int *gdy, int *way, int *wax);
    QTimer *timer;

public slots:
    void run();

signals:
    void resultReady(const QString &result);
};

#endif // TEXT_H
