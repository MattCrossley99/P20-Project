#include "sendWorker.h"
#include <QObject>
#include <QPointF>
#include <QDebug>
#include <QColor>
#include <QDataStream>
#include <QBuffer>


sendWorker::sendWorker(QObject *parent) :
    QObject(parent)
{
}

void sendWorker::sendTriggeredClear() {
    send("CL");
}

void sendWorker::sendMouseMoved(QPointF point) {
    QString coords;
    coords.append("MV");
    QString x2 = QString::number(point.x());
    QString y2 = QString::number(point.y());
    if (point.x() < 100) {
        x2.prepend("0");
    }
    if (point.x() < 10) {
        x2.prepend("0");
    }
    if (point.y() < 100) {
        y2.prepend("0");
    }
    if (point.y() < 10) {
        y2.prepend("0");
    }
    coords.append(x2);
    coords.append(y2);
    send(coords);
}

void sendWorker::sendMousePressed(QPointF point) {
    QString coords;

    coords.append("PD");
    QString x2 = QString::number(point.x());
    QString y2 = QString::number(point.y());
    if (point.x() < 100) {
        x2.prepend("0");
    }
    if (point.x() < 10) {
        x2.prepend("0");
    }
    if (point.y() < 100) {
        y2.prepend("0");
    }
    if (point.y() < 10) {
        y2.prepend("0");
    }
    coords.append(x2);
    coords.append(y2);
    send(coords);
}

void sendWorker::sendMouseReleased() {
   send("PU");
}

void sendWorker::sendUpdateModifiers(QColor pen, QColor bg, int width) {
    QString mods;
    mods.append("UM");
    QString width2;
    width2 = QString::number(width);
    if (width < 10) {
        width2.prepend("0");
    }
    mods.append(width2);
    mods.append(pen.name().right(6));
    mods.append(bg.name().right(6));
    send(mods);
}

void sendWorker::send(QString command){
    QString output;
    output.append("O");
    output.append(command);
    output.append("E");
    qDebug() << "Sent: " << output;
    QByteArray sendArray = output.toUtf8();
    emit sendPacket(sendArray);
}
