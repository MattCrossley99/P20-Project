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
    receiveStack.resize(150);
    int pos = 0;
    while(1) {
        pos = 0;
        //receiveStack.fill(false);
        while(packetSent == false) {
            while (sendReady == false) {}
            receiveReady = true;
            while(sendReady == true) {}
            receiveStack.setBit(pos,gpioData);
            pos++;
            if (pos > 144){
                pos = 0;
                break;
            }
            receiveReady = false;
            qDebug() << "i am a debug";

        }
        //emit packetOut(receiveStack);
        //receiveStack.fill(false);
        if((pos==32) | (pos == 80) | (pos == 144)){
            pos = 0;
            //qDebug() << receiveStack;
            emit packetOut(receiveStack);
        }
        pos = 0;
    }
}
