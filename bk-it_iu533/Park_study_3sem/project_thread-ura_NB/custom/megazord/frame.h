#ifndef FRAME_H
#define FRAME_H

#include "work.h"

class Frame {
private:
    Qt3DExtras::QCuboidMesh *planeMesh;
    Qt3DExtras::QPhongMaterial *planeMaterial;
    Qt3DCore::QTransform *planeTransform;
    Qt3DCore::QEntity *planeEntity;
public:
    float y;
    float width;

    Frame(Qt3DCore::QEntity *entity);
    void set_Y(Qt3DCore::QEntity *entity, float yy);
    void set_width(float w);
    void print_text(QString t);
};

#endif // FRAME_H
