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
    QPointF *holdingPoint = new QPointF;
    *holdingPoint = event->scenePos();
    if(holdingPoint->x() > 512){
        holdingPoint->setX(512);
    }
    if(holdingPoint->y() > 480){
         holdingPoint->setY(480);
    }
    if(holdingPoint->x() < 0){
        holdingPoint->setX(0);
    }
    if(holdingPoint->y() < 0){
         holdingPoint->setY(0);
    }
    emit signalMouseCoord(*holdingPoint);
    //qDebug() << "x:" << event->scenePos().x() << " y:" << event->scenePos().y();
}

void advancedScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPointF *holdingPoint = new QPointF;
    *holdingPoint = event->scenePos();
    if(holdingPoint->x() > 512){
        holdingPoint->setX(512);
    }
    if(holdingPoint->y() > 480){
         holdingPoint->setY(480);
    }
    emit signalPressCoord(*holdingPoint);
}

void advancedScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    emit signalRelease();
}
