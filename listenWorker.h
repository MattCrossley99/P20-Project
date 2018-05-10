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
    void exitLoop();
signals:
    void packetOut(QBitArray output);
public slots:
        int exec();
private:
       bool quitflag = 0;
       bool loopexited = 0;

};

#endif // LISTENWORKER_H
