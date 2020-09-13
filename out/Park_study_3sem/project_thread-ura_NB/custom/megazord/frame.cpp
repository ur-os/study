#include "frame.h"

Frame::Frame(Qt3DCore::QEntity *entity) {
    planeEntity = new Qt3DCore::QEntity(entity);

    planeMaterial = new Qt3DExtras::QPhongMaterial (planeEntity);

    planeMaterial->setDiffuse(QColor(rand() % 255+1,rand() % 255+1,rand() % 255+1));

    planeEntity->addComponent(planeMaterial);

}

void Frame::set_Y(Qt3DCore::QEntity *entity, float yy) {
        y = yy;

        planeTransform = new Qt3DCore::QTransform (entity);
        planeTransform->setTranslation(QVector3D(y, 0.0f, 0.0f));
        planeEntity->addComponent(planeTransform);

}

void Frame::set_width(float w) {
        width = w;

        planeMesh = new Qt3DExtras::QCuboidMesh(planeEntity);
        planeMesh->setZExtent(50.0f);
        planeMesh->setXExtent(w);
        planeMesh->setYExtent(0.1f);
        planeEntity->addComponent(planeMesh);
}

void Frame::print_text(QString t) {

    auto *text = new Qt3DCore::QEntity(planeEntity);

    auto *textMesh = new Qt3DExtras::QExtrudedTextMesh();
    textMesh->setDepth(.45f);
    QFont font("Baskerville Old Face", 32, -2, false);
    textMesh->setFont(font);
    textMesh->setText(t);

    auto *textMaterial = new Qt3DExtras::QPhongMaterial(planeEntity);
    textMaterial->setDiffuse(QColor(8, 181, 189));

    text->addComponent(textMesh);
    text->addComponent(textMaterial);


    Qt3DCore::QTransform* textTransform = new Qt3DCore::QTransform (planeEntity);
    textTransform->setTranslation(QVector3D(width/2-10, 1.0,20.0));

    text->addComponent(textTransform);
}
