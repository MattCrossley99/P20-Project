#include "window.h"
#include "ui_window.h"
#include "sendWorker.h"
#include "receiveWorker.h"
#include "listenWorker.h"

#include <QMessageBox>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QColorDialog>
#include <QBuffer>

bool gpioData;
bool sendReady;
bool receiveReady;
bool packetSent;

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    gpioData = 0;
    sendReady = 0;
    receiveReady = 0;
    packetSent = 1;

    QThread *sendThread = new QThread;
    sendWorker *sendworker = new sendWorker;
    sendworker->moveToThread(sendThread);
    //connects here
    connect(this, SIGNAL(signalSendCanvasCleared()), sendworker, SLOT(sendTriggeredClear()), Qt::QueuedConnection);
    connect(&canvas_send,SIGNAL(signalMouseCoord(QPointF)),sendworker,SLOT(sendMouseMoved(QPointF)), Qt::QueuedConnection);
    connect(&canvas_send,SIGNAL(signalPressCoord(QPointF)), sendworker, SLOT(sendMousePressed(QPointF)), Qt::QueuedConnection);
    connect(&canvas_send,SIGNAL(signalRelease()), sendworker, SLOT(sendMouseReleased()), Qt::QueuedConnection);
    connect(this, SIGNAL(signalUpdateModifiers(QColor,QColor,int)),sendworker, SLOT(sendUpdateModifiers(QColor,QColor,int)), Qt::QueuedConnection);

    QThread *receiveThread = new QThread;
    receiveWorker *receiveworker = new receiveWorker;
    receiveworker->moveToThread(receiveThread);
    connect(receiveworker, SIGNAL(rcvUpdateModifiers(QColor,QColor,int)), this, SLOT(receiveWindow_updateMods(QColor,QColor,int)), Qt::QueuedConnection);
    connect(receiveworker, SIGNAL(rcvClearWindow()), this, SLOT(receiveWindow_clearScreen()), Qt::QueuedConnection);
    connect(receiveworker, SIGNAL(rcvPenDown(int,int)),this,SLOT(receiveWindow_PenDown(int,int)),Qt::QueuedConnection);
    connect(receiveworker, SIGNAL(rcvMove(int,int)), this, SLOT(receiveWindow_Move(int,int)), Qt::QueuedConnection);

    QThread *listenThread = new QThread;
    listenWorker *listenworker = new listenWorker;
    listenworker->moveToThread(listenThread);
    //connects
    connect(listenworker, SIGNAL(packetOut(QBitArray)), receiveworker, SLOT(receivePacket(QBitArray)), Qt::QueuedConnection);
    connect(listenThread, &QThread::started, listenworker, &listenWorker::exec);

    sendThread->start();
    receiveThread->start();
    listenThread->start();

    connect(&canvas_send,SIGNAL(signalMouseCoord(QPointF)),this,SLOT(sendWindow_mouseMoved(QPointF)));
    connect(&canvas_send,SIGNAL(signalPressCoord(QPointF)),this,SLOT(sendWindow_mousePressed(QPointF)));

    ui->graphicsView_send->setScene(&canvas_send);
    canvas_send.setSceneRect(0,0,512,480);
    canvas_send.setBackgroundBrush(Qt::white);
    ui->graphicsView_receive->setScene(&canvas_receive);
    canvas_receive.setSceneRect(0,0,512,480);
    canvas_receive.setBackgroundBrush(Qt::white);
    pen_send.setCapStyle(Qt::RoundCap);
    pen_receive.setCapStyle(Qt::RoundCap);
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

void Window::sendWindow_mousePressed(QPointF point){
    mousePrevX = point.x();
    mousePrevY = point.y();
}


void Window::on_actionClear_triggered()
{
    canvas_send.clear();
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
    emit signalUpdateModifiers(pen_send.color(),canvas_send.backgroundBrush().color(),pen_send.width());
}

void Window::on_spinBox_valueChanged(int arg1)
{
    pen_send.setWidth(arg1);
    emit signalUpdateModifiers(pen_send.color(),canvas_send.backgroundBrush().color(),pen_send.width());
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
    emit signalUpdateModifiers(pen_send.color(),canvas_send.backgroundBrush().color(),pen_send.width());
}

 void Window::receiveWindow_updateMods(QColor fg, QColor bg, int width) {
     canvas_receive.setBackgroundBrush(bg);
     pen_receive.setColor(fg);
     pen_receive.setWidth(width);
 }

 void Window::receiveWindow_clearScreen() {
     canvas_receive.clear();
 }

 void Window::receiveWindow_PenDown(int x, int y) {
     rcvPrevX = x;
     rcvPrevY = y;
     //qDebug() << "Pen Down";
 }

 void Window::receiveWindow_Move(int x, int y) {
     canvas_receive.addLine(rcvPrevX,rcvPrevY,x,y,pen_receive);
     rcvPrevX = x;
     rcvPrevY = y;
     //qDebug() << "Drawing";
 }
