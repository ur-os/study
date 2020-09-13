#include "cube.h"
#include "work.h"
#include <QObject>

void Cube::handlePickerClicked(Qt3DRender::QPickEvent *event) {
    if (!addrForPoint.isEmpty()) {
        float y = view->map[addrForPoint].y();
        float x = view->map[addrForPoint].x();
        view->camera()->setUpVector(QVector3D(0.0f, 50.0f, 0.0f));
        view->camera()->setViewCenter(QVector3D(x, 0.0f , y));
        view->camera()->setPosition(QVector3D(x, 40.f, y + 50.0f));
        addrForPoint.clear();
        qDebug()<<QString::number(y);
        qDebug()<<QString::number(x);

    }
    qDebug()<<QString("lol");
}

void Cube::createObjectPicker(MyWindow *v) {
    view = v;
    objectPicker = new Qt3DRender::QObjectPicker(cuboidEntity);

    QObject::connect(objectPicker, &Qt3DRender::QObjectPicker::clicked, this, &Cube::handlePickerClicked);

    cuboidEntity->addComponent(objectPicker);
}

Cube::Cube(Qt3DCore::QEntity *entity, Qube *q) {
    enum Type_Cube type = get_type(q);
    QColor color = get_color(type);

   // if (type == ) {

    //}

    name = q->name;
    this->type = q->type;
    addr = q->addr;
    content = q-> content;
    scope = q->scope;

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
    textMaterial->setDiffuse(QColor(86,74,73));

    text->addComponent(textMesh);
    text->addComponent(textMaterial);

    Qt3DCore::QTransform* textTransform = new Qt3DCore::QTransform (cuboidEntity);
    if (id % 2 == 0) {
        textTransform->setTranslation(QVector3D(-5.0, z, 10.0));
    } else {
        textTransform->setTranslation(QVector3D(-5.0, z-5, 15.0));
    }
    text->addComponent(textTransform);
}
