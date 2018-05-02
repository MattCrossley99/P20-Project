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
    void sendPacket(QByteArray output);
public slots:
    void sendTriggeredClear();
    void sendMouseMoved(QPointF point);
    void sendMousePressed(QPointF point);
    void sendMouseReleased();
    void sendUpdateModifiers(QColor pen, QColor bg, int width);

private:
    void send(QString command);
};

#endif // SENDWORKER_H
