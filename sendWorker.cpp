#include "sendWorker.h"
#include <QObject>
#include <QPointF>
#include <QDebug>
#include <QColor>

sendWorker::sendWorker(QObject *parent) :
    QObject(parent)
{
}

void sendWorker::sendTriggeredClear() {
    //encode and send OCLE
    qDebug() << "Clear Triggered";
}

void sendWorker::sendMouseMoved(QPointF point) {
    //encode and send OMVXXXYYYE
     qDebug() << point.x() << " " << point.y();
}

void sendWorker::sendMousePressed(QPointF point) {
    //encode and send OPDXXXYYYE
     qDebug() << point.x() << " " << point.y();
}

void sendWorker::sendMouseReleased() {
   //encode and send OPUE
    qDebug() << "Mouse was released!";
}

void sendWorker::sendUpdateModifiers(QColor pen, QColor bg, int width) {
    //encode and send OUMXXXXXXXXXXXXXXE
    qDebug() << pen.name() << " " << bg.name() << " " << width;
}
