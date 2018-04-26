#ifndef SENDWORKER_H
#define SENDWORKER_H

#include <QObject>
#include <QThread>
#include <QPointF>

class sendWorker : public QObject
{
    Q_OBJECT
public:
    explicit sendWorker(QObject *parent = 0);
signals:

public slots:
    void sendTriggeredClear();
    void sendMouseMoved(QPointF point);
    void sendMousePressed(QPointF point);
    void sendMouseReleased();

};

#endif // SENDWORKER_H
