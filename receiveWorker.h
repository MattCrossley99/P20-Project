#ifndef RECEIVEWORKER_H
#define RECEIVEWORKER_H

#include <QObject>
#include <QByteArray>
#include <QBitArray>
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
    void rcvPenDown(int x, int y);
    void rcvMove(int x, int y);

public slots:
    void receivePacket(QBitArray bits);
    void analysePacket(QString input);
private:

};

#endif // RECEIVEWORKER_H
