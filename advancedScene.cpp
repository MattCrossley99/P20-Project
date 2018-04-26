//subclass idea based on evileg.com gamedev page

#include "advancedScene.h"
#include <QDebug>
#include <QPointF>

advancedScene::advancedScene(QObject *parent) :
    QGraphicsScene()
{
    Q_UNUSED(parent);
}

advancedScene::~advancedScene()
{

}

void advancedScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    emit signalMouseCoord(event->scenePos());
    //qDebug() << "x:" << event->scenePos().x() << " y:" << event->scenePos().y();
}

void advancedScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF *holdingPoint = new QPointF;
    *holdingPoint = event->scenePos();
    if(holdingPoint->x() > 480){
        holdingPoint->setX(480);
    }
    if(holdingPoint->y() > 512){
         holdingPoint->setY(512);
    }
    emit signalPressCoord(*holdingPoint);
}

void advancedScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    emit signalRelease();
}
