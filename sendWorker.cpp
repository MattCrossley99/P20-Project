#include "sendWorker.h"
#include <QObject>
#include <QPointF>
#include <QDebug>
#include <QColor>
#include <QDataStream>
#include <QBitArray>
#include <QByteArray>
#include "wiringPi.h"

/*pinMode(21,OUTPUT);
pinMode(22,OUTPUT);
pinMode(23,OUTPUT);
pinMode(26,OUTPUT);*/

#define packetSent 21
#define sendReady 22
#define receiveReady 23
#define gpioData 26

/*extern bool gpioData;
extern bool sendReady;
extern bool packetSent;
extern bool receiveReady;*/

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
    //qDebug() << "Sent: " << output;
    QByteArray sendArray = output.toUtf8();
    QBitArray commandBinary(sendArray.count()*8);

    for(int i=0; i<sendArray.count(); i++) {
        for(int j=0; j<8;j++) {
            commandBinary.setBit(i*8+j, sendArray[i]&(1<<(7-j)));
        }
    }
    qDebug() << "Bit array: " << commandBinary << endl;
    writeToGPIO(commandBinary);
}

void sendWorker::writeToGPIO(QBitArray data) {
    qDebug() << "5";
    digitalWrite(packetSent,LOW);
    qDebug() << "6";
    for(int i = 0; i < data.count(); i++) {
        qDebug() << data[i];
        digitalWrite(sendReady,HIGH);
        while(digitalRead(receiveReady) == 0) {}
        digitalWrite(gpioData,data[i]);
        //qDebug() << "Data sent: " << gpioData;
        digitalWrite(sendReady,LOW);
        while(digitalRead(receiveReady) == 1) {}

    }
    //qDebug() << "12";
    digitalWrite(packetSent,HIGH);
}
