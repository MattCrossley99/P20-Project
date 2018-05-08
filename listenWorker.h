#ifndef LISTENWORKER_H
#define LISTENWORKER_H

#include <QObject>
#include <QBitArray>
#include <QThread>

class listenWorker : public QObject
{
    Q_OBJECT
public:
    explicit listenWorker(QObject *parent = 0);

signals:
    void packetOut(QBitArray output);
public slots:
    int exec();
protected:

};

#endif // LISTENWORKER_H
