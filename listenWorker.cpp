#include "listenWorker.h"
#include <QBitArray>
#include <QDebug>


extern bool gpioData;
extern bool sendReady;
extern bool receiveReady;
extern bool packetSent;

listenWorker::listenWorker(QObject *parent) :
    QObject(parent)
{
}

int listenWorker::exec() {
    qDebug() << "Listen thread started!";
    QBitArray receiveStack;
    receiveStack.resize(256);
    int pos = 0;
    while(1) {
        while(packetSent == false) {
            qDebug() << "0";
            receiveReady = true;
            qDebug() << "1";
            while(sendReady == true) {}
            qDebug() << "2";
            receiveReady = false;
            qDebug() << "3";
            receiveStack.setBit(pos,gpioData);
            qDebug() << "4";
            pos++;
            qDebug() << gpioData << "Position: " << pos;
        }
        //emit packetOut(receiveStack);
        //receiveStack.fill(false);
        if((pos==32) | (pos == 80) | (pos == 144)){
            pos = 0;
            qDebug() << receiveStack;
            emit packetOut(receiveStack);
            receiveStack.fill(false);
        }
        pos = 0;
    }
}
