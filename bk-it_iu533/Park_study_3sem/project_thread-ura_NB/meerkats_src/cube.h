#ifndef CUBE_H
#define CUBE_H

#include "work.h"
#include <QObject>

class Cube : public QObject{
    Q_OBJECT
    MyWindow *view;
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

public slots:
    void handlePickerClicked(Qt3DRender::QPickEvent *event);

public:
    float y,z;
    int id;

    QString addr;
    QString type;
    QString scope;
    QString name;
    QString content;
    QString addrForPoint;
    //int pointTo[3];

    Cube(Qt3DCore::QEntity *entity, Qube* q);
    void set_YZ(Qt3DCore::QEntity* entity);
    void print_text();
    void text1(QString str,float z);

    void createObjectPicker(MyWindow* view);
};

#endif // CUBE_H
