#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>
#include <QThread>
#include "advancedScene.h"
#include "listenWorker.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Window(QWidget *parent = 0);
    ~Window();

signals:
    void signalSendCanvasCleared();
    void signalUpdateModifiers(QColor pen, QColor bg, int width);
    void signalKillThread();
    
private slots:
    void on_actionQuit_triggered();

    void sendWindow_mouseMoved(QPointF point);

    void sendWindow_mousePressed(QPointF point);

    void on_actionClear_triggered();

    void on_comboBox_2_activated(int index);

    void on_spinBox_valueChanged(int arg1);

    void on_comboBox_activated(int index);

    void receiveWindow_updateMods(QColor fg, QColor bg, int width);

    void receiveWindow_clearScreen();

    void receiveWindow_PenDown(int x, int y);

    void receiveWindow_Move(int x, int y);

private:
    Ui::Window *ui;
    advancedScene canvas_send;
    QPen pen_send;
    advancedScene canvas_receive;
    QPen pen_receive;
    qreal mousePrevX = 0;
    qreal mousePrevY = 0;
    qreal rcvPrevX = 0;
    qreal rcvPrevY = 0;
    QColor penColour;
    QColor send_backgroundColour;
    QThread sendThread;
    QThread receiveThread;
    QThread listenThread;
};

#endif // WINDOW_H
