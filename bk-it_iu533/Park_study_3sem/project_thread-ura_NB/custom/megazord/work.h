#ifndef WORK_H
#define WORK_H

#include <Qt3DRender>
#include <QString>

#include "mywindow.h"

enum Type_Cube{
    Cube_INT,
    Cube_FLOAT,
    Cube_POINT,
    Cube_CHAR,
};

void *createEntity(QVector <QVector <QVector <Qube>>>& array);
QColor get_color(enum Type_Cube type);
enum Type_Cube get_type (const Qube* q);

void QubetoCube();

#endif // WORK_H
