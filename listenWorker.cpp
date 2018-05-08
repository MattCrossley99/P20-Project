#include "listenWorker.h"
#include <QBitArray>
#include <QDebug>
#include "wiringPi.h"

/*pinMode(27,INPUT);
pinMode(28,INPUT);
pinMode(29,INPUT);
pinMode(25,INPUT);*/

#define packetSent 27
#define sendReady 28
#define receiveReady 29
#define gpioData 25

/*extern bool gpioData;
extern bool sendReady;
extern bool receiveReady;
extern bool packetSent;*/

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
        while(digitalRead(packetSent) == 0) {
            qDebug() << "1";
            while (digitalRead(sendReady) == 0) {}
            digitalWrite(receiveReady,HIGH);
            while(digitalRead(sendReady) == 1) {}
            receiveStack.setBit(pos,digitalRead(gpioData));
            pos++;
            if (pos > 144){
                pos = 0;
                break;
            }
            digitalWrite(receiveReady,LOW);
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
