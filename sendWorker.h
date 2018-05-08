#ifndef SENDWORKER_H
#define SENDWORKER_H

#include <QObject>
#include <QThread>
#include <QPointF>
#include <QColor>
#include <QDataStream>
#include <QByteArray>

class sendWorker : public QObject
{
    Q_OBJECT
public:
    explicit sendWorker(QObject *parent = 0);
signals:
    void sendReceive();
public slots:
    void sendTriggeredClear();
    void sendMouseMoved(QPointF point);
    void sendMousePressed(QPointF point);
    void sendMouseReleased();
    void sendUpdateModifiers(QColor pen, QColor bg, int width);

private:
    void send(QString command);
    void writeToGPIO(QBitArray data);
};

#endif // SENDWORKER_H
