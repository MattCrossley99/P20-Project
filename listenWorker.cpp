#include "listenWorker.h"
#include <QBitArray>
#include <QDebug>

listenWorker::listenWorker(QObject *parent) :
    QObject(parent)
{
}


extern bool gpioData;
extern bool sendReady;
extern bool receiveReady;
extern bool packetSent;

int listenWorker::exec() {
    qDebug() << "Listen thread started!";
    QBitArray receiveStack;
    //receiveStack.resize(100);
    int pos = 0;
    while(1) {
        while(packetSent == false) {
            receiveReady = true;
            while(sendReady == true) {};
            receiveStack.setBit(pos,gpioData);
            qDebug() << gpioData;
            receiveReady = false;
            pos++;
            if((pos==32) | (pos == 80) | (pos == 144)){
                pos = 0;
                emit packetOut(receiveStack);
            }
        }
    }
}
