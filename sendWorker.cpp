#include "sendWorker.h"
#include <QObject>
#include <QPointF>
#include <QDebug>

sendWorker::sendWorker(QObject *parent) :
    QObject(parent)
{
}

void sendWorker::sendTriggeredClear() {
    //encode and send OCLE
    qDebug() << "Clear Triggered";
}

void sendWorker::sendMouseMoved(QPointF point) {
    //encode and send OMVXXXYYYWCDE
     qDebug() << point.x() << " " << point.y();
}

void sendWorker::sendMousePressed(QPointF point) {
    //encode and send OPDXXXYYYWCDE
     qDebug() << point.x() << " " << point.y();
}

void sendWorker::sendMouseReleased() {
   //encode and send OPUE
    qDebug() << "Mouse was released!";
}
