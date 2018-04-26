//subclass idea based on evileg.com gamedev page

#ifndef ADVANCEDSCENE_H
#define ADVANCEDSCENE_H

#endif // ADVANCEDSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class advancedScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit advancedScene(QObject *parent = 0);
    ~advancedScene();

signals:
    void signalMouseCoord(QPointF point);
    void signalPressCoord(QPointF point);
    void signalRelease();

private:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};
