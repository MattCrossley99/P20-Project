#ifndef GPIOWORKER_H
#define GPIOWORKER_H

#include <QObject>
#include <QByteArray>
#include <QBitArray>

class gpioWorker : public QObject
{
    Q_OBJECT
public:
    explicit gpioWorker(QObject *parent = 0);
signals:
    void outgoingData(QByteArray outBits);
public slots:
    void incomingData(QByteArray incBytes);
    void bitsToBytes(QBitArray bits);
private:
    bool data = 0;
    bool sync = 0;

};

#endif // GPIOWORKER_H
