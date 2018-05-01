#include "sendWorker.h"
#include <QObject>
#include <QPointF>
#include <QDebug>
#include <QColor>
#include <QDataStream>
#include <QFile>


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
    coords.append(QString::number(point.x()));
    coords.append(QString::number(point.y()));
    send(coords);
}

void sendWorker::sendMousePressed(QPointF point) {
    QString coords;
    coords.append("PD");
    coords.append(QString::number(point.x()));
    coords.append(QString::number(point.y()));
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
    QFile file("testoutput.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << output;
}
