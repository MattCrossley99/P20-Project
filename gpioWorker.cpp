//thanks to QT wiki

#include "gpioWorker.h"

#include <QBitArray>
#include <QByteArray>
#include <QDebug>
#include <QString>

gpioWorker::gpioWorker(QObject *parent) :
    QObject(parent)
{
}

void gpioWorker::incomingData(QByteArray incBytes){
    QBitArray commandBinary(incBytes.count()*8);

    for(int i=0; i<incBytes.count(); i++) {
        for(int j=0; j<8;j++) {
            commandBinary.setBit(i*8+j, incBytes[i]&(1<<(7-j)));
        }
    }
    //qDebug() << "Bit array: " << commandBinary << endl;
    sync = 1;
    writeToGPIO(commandBinary);
    sync = 0;
}

void gpioWorker::bitsToBytes(QBitArray bits) {
    QByteArray commandData;
    commandData.resize(bits.count()/8+1);
    commandData.fill(0);
    for(int i=0; i<bits.count(); i++) {
        commandData[i/8] = (commandData.at(i/8) | ((bits[i]?1:0)<<(7-(i%8))));
    }
    emit outgoingData(commandData);
}

void gpioWorker::writeToGPIO(QBitArray bits){

}

QBitArray gpioWorker::readFromGPIO(){

}
