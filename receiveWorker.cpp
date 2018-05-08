#include "receiveWorker.h"
#include <QObject>
#include <QPointF>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QDataStream>
#include <QColor>
#include <QPen>
#include <QBitArray>
#include <QByteArray>

extern bool gpioData;
extern bool sendReady;
extern bool receiveReady;
extern bool packetSent;

receiveWorker::receiveWorker(QObject *parent) :
    QObject(parent)
{

}

void receiveWorker::receivePacket(QBitArray bits) {
    QByteArray commandData;
    commandData.resize(bits.count()/8+1);
    commandData.fill(0);
    for(int i=0; i<bits.count(); i++) {
        commandData[i/8] = (commandData.at(i/8) | ((bits[i]?1:0)<<(7-(i%8))));
   }
   QString inputCommand;
   inputCommand = commandData;
   qDebug() << inputCommand;
   //analysePacket(inputCommand);
   //qDebug() << "Returned from analysis";
}

void receiveWorker::analysePacket(QString input) {
    if(input[0] != QChar('O')){
        qDebug() << "Packet error";
        return;
    }
    QString commandCode;
    commandCode.append(input[1]);
    commandCode.append(input[2]);
    if (commandCode == "PU") {
        //penup
    }
    if (commandCode == "PD") {
        //pendown
        int x = input.mid(3,3).toInt();
        int y = input.mid(6,3).toInt();
        emit rcvPenDown(x,y);
    }
    if (commandCode == "MV") {
        //move pen
        int x = input.mid(3,3).toInt();
        int y = input.mid(6,3).toInt();
        emit rcvMove(x,y);
    }
    if (commandCode == "CL") {
        //clear canvas
        emit rcvClearWindow();
    }
    if (commandCode == "UM") {
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
    }
    return;
}

void receiveWorker::readFromGPIO() {
    /*QBitArray receiveStack;
    receiveStack.resize(100);
    int pos = 0;
    while(packetSent == false) {
        qDebug() << gpioData;
        receiveReady = true;
        while(sendReady == true) {};
        receiveStack.setBit(pos,gpioData);
        receiveReady = false;
        pos++;
        qDebug() << "looped, position = " << pos;
    }
    pos = 0;
    qDebug() << receiveStack;
    receivePacket(receiveStack);*/
    qDebug() << "SLOT Activated";
}
