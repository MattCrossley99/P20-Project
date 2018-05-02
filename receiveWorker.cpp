#include "receiveWorker.h"
#include <QObject>
#include <QPointF>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QDataStream>
#include <QColor>
#include <QPen>

receiveWorker::receiveWorker(QObject *parent) :
    QObject(parent)
{

}

void receiveWorker::receivePacket(QByteArray input) {
   QString inputCommand;
   qDebug() << "Received: " << input;
   inputCommand = input;
   qDebug() << "Converted: " << inputCommand;
   analysePacket(input);
}

void receiveWorker::analysePacket(QString input) {
    if(input[0] =! "O"){
        return;
    }
    QString commandCode;
    commandCode.append(input[1]);
    commandCode.append(input[2]);
    enum
    switch (commandCode)
    case "PU":
        //penup
    case "PD":
        //pendown
    case "MV":
        //move
    case "AK":
        //acknowledge
    case "RQ":
        //request acknowledge
    case "CL":
        //clear canvas
    case "UM":
        QColor fg;
        QColor bg;
        int width;
        QString holder;
        holder = input.mid(3,2);
        width = holder.toInt();
        holder = "";
        holder = "#";
        holder += input.mid(5,6);
        fg.setNamedColor(holder);
        holder = "";
        holder = "#";
        holder += input.midRef(11,6);
        bg.setNamedColor(holder);
        emit rcvUpdateModifiers(fg, bg, width);

    default:
        return;
}
