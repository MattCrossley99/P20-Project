#ifndef RECEIVEWORKER_H
#define RECEIVEWORKER_H

#include <QObject>
#include <QByteArray>
#include <QColor>

namespace Ui {
class receiveWorker;
}

class receiveWorker : public QObject
{
    Q_OBJECT
public:
    explicit receiveWorker(QObject *parent = 0);

signals:
    void rcvUpdateModifiers(QColor pen, QColor bg, int width);
    void rcvClearWindow();

public slots:
    void receivePacket(QByteArray input);
    void analysePacket(QString input);
};

#endif // RECEIVEWORKER_H
