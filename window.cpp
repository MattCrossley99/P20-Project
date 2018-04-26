#include "window.h"
#include "ui_window.h"

#include <QMessageBox>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QDebug>
#include <QThread>
#include "sendWorker.h"

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    QThread *sendThread = new QThread;
    sendWorker *sendworker = new sendWorker;
    sendworker->moveToThread(sendThread);
    //connects here
    connect(this, SIGNAL(signalSendCanvasCleared()), sendworker, SLOT(sendTriggeredClear()), Qt::QueuedConnection);
    connect(&canvas_send,SIGNAL(signalMouseCoord(QPointF)),sendworker,SLOT(sendMouseMoved(QPointF)), Qt::QueuedConnection);
    connect(&canvas_send,SIGNAL(signalPressCoord(QPointF)), sendworker, SLOT(sendMousePressed(QPointF)), Qt::QueuedConnection);
    connect(&canvas_send,SIGNAL(signalRelease()), sendworker, SLOT(sendMouseReleased()), Qt::QueuedConnection);

    sendThread->start();

    connect(&canvas_send,SIGNAL(signalMouseCoord(QPointF)),this,SLOT(sendWindow_mouseMoved(QPointF)));

    ui->graphicsView_send->setScene(&canvas_send);
    canvas_send.setSceneRect(0,0,512,480);
    ui->graphicsView_receive->setScene(&canvas_receive);
    canvas_receive.setSceneRect(0,0,512,480);
}

Window::~Window()
{
    delete ui;
}

void Window::on_actionQuit_triggered()
{
    int exitChoice = QMessageBox::warning(this, tr("Quit"), tr("Are you sure?"), QMessageBox::No | QMessageBox::Yes);
        if(exitChoice == QMessageBox::Yes){
            QApplication::quit();
        }
}

void Window::sendWindow_mouseMoved(QPointF point)
{
    ui->xMousePos->setPlainText(QString::number(point.x()));
    ui->yMousePos->setPlainText(QString::number(point.y()));
    if(QApplication::mouseButtons() == Qt::LeftButton && mousePrevX != 0 && mousePrevY != 0){
        this->canvas_send.addLine(mousePrevX,mousePrevY,point.x(),point.y(),this->pen_send);
    }
    mousePrevX = point.x();
    mousePrevY = point.y();
    //transmission thread: send coords and a move command
}


void Window::on_actionClear_triggered()
{
    this->canvas_send.clear();
    emit signalSendCanvasCleared();
    //transmission thread: send a clear command
}
