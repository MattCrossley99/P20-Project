#ifndef RECEIVEWORKER_H
#define RECEIVEWORKER_H

#include <QObject>

class receiveWorker : public QObject
{
    Q_OBJECT
public:
    explicit receiveWorker(QObject *parent = nullptr);

signals:

public slots:
};

#endif // RECEIVEWORKER_H