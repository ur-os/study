#ifndef CUBE_H
#define CUBE_H

#include "work.h"

class Cube_object : public QObject {
    Q_OBJECT
public:
    MyWindow *view;
public slots:
    void handlePickerClicked(Qt3DRender::QPickEvent *event);
};

class Cube {
private:

    Qt3DCore::QEntity* cuboidEntity;
    Qt3DExtras::QCuboidMesh* cuboidMesh;
    Qt3DExtras::QPhongMaterial* cuboidMaterial;
    Qt3DCore::QTransform* cuboidTransform;

    Qt3DExtras::QNormalDiffuseSpecularMapMaterial* normalDiffuseSpecularMapMaterial;
    Qt3DRender::QTextureImage* diffuseImage;
    Qt3DRender::QTextureImage* specularImage;
    Qt3DRender::QTextureImage* normalImage;

    Qt3DRender::QObjectPicker* objectPicker;

    Cube_object* object;

public:
    float y,z;


    QString addr;
    QString type;
    QString scope;
    QString name;
    QString content;

    Cube(Qt3DCore::QEntity *entity, Qube* q);
    ~Cube();
    void set_YZ(Qt3DCore::QEntity* entity);
    void print_text();
    void text1(QString str,float z);

    void createObjectPicker(MyWindow* view);
};

#endif // CUBE_H
