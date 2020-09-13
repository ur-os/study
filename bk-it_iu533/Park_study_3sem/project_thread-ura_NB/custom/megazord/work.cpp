#include "work.h"
#include "cube.h"
#include "frame.h"



enum Type_Cube get_type (const Qube *q) {
    QByteArray str(q->type);
    if (str.indexOf("*") != -1)
        return Cube_POINT;
    if (str.indexOf("int") != -1)
        return Cube_INT;
    if (str.indexOf("char") != -1)
        return Cube_INT;
    if (str.indexOf("float") != -1)
        return Cube_FLOAT;
    if (str.indexOf("double") != -1)
        return Cube_FLOAT;
    return Cube_INT;
}

QColor get_color(enum Type_Cube type) {
    switch (type) {
        case Cube_INT: return QColor(255,159,128);
        case Cube_FLOAT: return QColor(209,242,165);
        case Cube_POINT: return QColor(169,37,200);
        default: return QColor(0,0,0);
    }
}
