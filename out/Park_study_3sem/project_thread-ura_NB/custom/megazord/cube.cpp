#include "cube.h"
#include "work.h"
#include <QObject>

void Cube_object::handlePickerClicked(Qt3DRender::QPickEvent *event) {

  view->camera()->setUpVector(QVector3D(0.0f, 50.0f, 0.0f));
  view->camera()->setPosition(QVector3D(60.0f, 60.0f, 60.0f));
  view->camera()->setViewCenter(QVector3D(-15.0f, 0.0f, 0.0f));

}

void Cube::createObjectPicker(MyWindow *v) {
    object->view = v;
    objectPicker = new Qt3DRender::QObjectPicker(cuboidEntity);

    QObject::connect(objectPicker, &Qt3DRender::QObjectPicker::clicked, this->object, &Cube_object::handlePickerClicked);

    cuboidEntity->addComponent(objectPicker);
}

Cube::Cube(Qt3DCore::QEntity *entity, Qube *q) {
    enum Type_Cube type = get_type(q);
    QColor color = get_color(type);

    name = q->name;
    this->type = q->type;
    addr = q->addr;
    content = q-> content;
    scope = q->scope;

    object = new Cube_object;

    cuboidMesh = new Qt3DExtras::QCuboidMesh(entity);
    cuboidMesh->setXExtent(10.0f);
    cuboidMesh->setYExtent(10.0f);
    cuboidMesh->setZExtent(10.0f);

    cuboidMaterial = new Qt3DExtras::QPhongMaterial (entity);
    cuboidMaterial->setDiffuse(color);

    cuboidEntity = new Qt3DCore::QEntity(entity);
    cuboidEntity->addComponent(cuboidMesh);
    cuboidEntity->addComponent(cuboidMaterial);

}

void Cube::set_YZ(Qt3DCore::QEntity *entity) {
    cuboidTransform = new Qt3DCore::QTransform (entity);
    cuboidTransform->setTranslation(QVector3D(this->y, this->z, 0.0f));
    cuboidEntity->addComponent(cuboidTransform);
}

void Cube::print_text() {
    text1(QString("Name: ") + name, 5.0);
    text1(QString("Type: ") + type, 3.5);
    text1(QString("Content: ") + content, 2.0);
    text1(QString("Address: ") + addr, 0.5);
}

void Cube::text1(QString str, float z) {
    auto *text = new Qt3DCore::QEntity(cuboidEntity);

    auto *textMesh = new Qt3DExtras::QExtrudedTextMesh();

    textMesh->setDepth(.45f);
    QFont font("Baskerville Old Face", 35, -1, false);
    textMesh->setFont(font);
    textMesh->setText(str);

    auto *textMaterial = new Qt3DExtras::QPhongMaterial(cuboidEntity);
    textMaterial->setDiffuse(QColor(51, 150, 100));

    text->addComponent(textMesh);
    text->addComponent(textMaterial);

    Qt3DCore::QTransform* textTransform = new Qt3DCore::QTransform (cuboidEntity);
    textTransform->setTranslation(QVector3D(-5.0, z, 10.0));

    text->addComponent(textTransform);

}
