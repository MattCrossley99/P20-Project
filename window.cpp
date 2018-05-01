#include "window.h"
#include "ui_window.h"

#include <QMessageBox>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QColorDialog>
#include "sendWorker.h"
#include "receiveWorker.h"

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
    QThread *receiveThread = new QThread;
    receiveWorker *receiveworker = new receiveWorker;
    receiveworker->moveToThread(receiveThread);
    //add receive connects

    sendThread->start();
    receiveThread->start();

    connect(&canvas_send,SIGNAL(signalMouseCoord(QPointF)),this,SLOT(sendWindow_mouseMoved(QPointF)));

    ui->graphicsView_send->setScene(&canvas_send);
    canvas_send.setSceneRect(0,0,512,480);
    ui->graphicsView_receive->setScene(&canvas_receive);
    canvas_receive.setSceneRect(0,0,512,480);
    pen_send.setCapStyle(Qt::RoundCap);
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

void Window::on_comboBox_2_activated(int index)
{
    switch (index) {
    case 0:
        penColour = Qt::black;
        break;
    case 1:
        penColour = Qt::white;
        break;
    case 2:
        penColour = Qt::red;
        break;
    case 3:
        penColour = Qt::blue;
        break;
    case 4:
        penColour = Qt::green;
        break;
    case 5:
        penColour = Qt::magenta;
        break;
    case 6:
        penColour = Qt::yellow;
        break;
    case 7:
        penColour = QColorDialog::getColor(penColour, this);
        break;
    default:
        break;
    }
    pen_send.setColor(penColour);
}

void Window::on_spinBox_valueChanged(int arg1)
{
    pen_send.setWidth(arg1);
}

void Window::on_comboBox_activated(int index)
{
    switch (index) {
    case 0:
        send_backgroundColour = Qt::white;
        break;
    case 1:
        send_backgroundColour = Qt::black;
        break;
    case 2:
        send_backgroundColour = Qt::cyan;
        break;
    case 3:
        send_backgroundColour = Qt::magenta;
        break;
    case 4:
        send_backgroundColour = Qt::yellow;
        break;
    case 5:
        send_backgroundColour = QColorDialog::getColor(send_backgroundColour, this);
        break;
    default:
        break;
    }
    canvas_send.setBackgroundBrush(send_backgroundColour);
}
