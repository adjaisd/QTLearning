// You may need to build the project (run Qt uic code generator) to get "ui_WinServer.h" resolved

#include <QMessageBox>
#include <QGridLayout>
#include <QPushButton>
#include "winserver.h"
#include "ui_winserver.h"


WinServer::WinServer(QWidget *parent) :
        QWidget(parent), ui(new Ui::WinServer) {
    ui->setupUi(this);
    ledImgButton = new QPushButton;
    ledImgButton->setIconSize(QSize(WIDTH, HEIGHT));
    ledImgButton->setIcon(QIcon("://images/off.png"));

    ledCtrlButton = new QPushButton("打开厨房灯");

    machImgButton = new QPushButton;
    machImgButton->setIconSize(QSize(WIDTH, HEIGHT));
    machImgButton->setIcon(QIcon("://images/power.png"));

    machCtrlButton = new QPushButton("打开油烟机");

    auto *glayout = new QGridLayout(this);
    glayout->addWidget(ledImgButton, 0, 0);
    glayout->addWidget(machImgButton, 0, 1);
    glayout->addWidget(ledCtrlButton, 1, 0);
    glayout->addWidget(machCtrlButton, 1, 1);

    WinServer::connect(ledCtrlButton, SIGNAL(clicked(bool)), this, SLOT(slotCtrlLed()));
    WinServer::connect(machCtrlButton, SIGNAL(clicked(bool)), this, SLOT(slotCtrlMach()));

    isOpenLed = false;
    isOpenMach = false;

    tcpSocket = nullptr;
    tcpServer = new QTcpServer(this);
    //bool isListen = tcpServer -> listen(QHostAddress("192.168.31.229"), 10000);
    bool isListen = tcpServer->listen(QHostAddress("localhost"), 10000);
    if (!isListen) {
        QMessageBox::critical(this, "listen error.", "ip or port error.");
    }
    WinServer::connect(tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

WinServer::~WinServer() {
    delete ui;
}

void WinServer::slotCtrlLed() {
    isOpenLed = !isOpenLed;
    if (isOpenLed) {
        ledImgButton->setIcon(QIcon("://images/on.png"));
        ledCtrlButton->setText("关闭厨房灯");
    } else {
        ledImgButton->setIcon(QIcon("://images/off.png"));
        ledCtrlButton->setText("打开厨房灯");
    }
}

void WinServer::slotCtrlMach() {
    isOpenMach = !isOpenMach;
    if (isOpenMach) {
        machImgButton->setIcon(QIcon("://images/open.png"));
        machCtrlButton->setText("关闭油烟机");
    } else {
        machImgButton->setIcon(QIcon("://images/power.png"));
        machCtrlButton->setText("打开油烟机");
    }
}

void WinServer::slotNewConnection() {
    if (nullptr == tcpSocket && tcpServer->hasPendingConnections()) {
        tcpSocket = tcpServer->nextPendingConnection();
        WinServer::connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(slotReadData()));
        WinServer::connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnection()));
    }
}

void WinServer::slotDisconnection() {
    if (nullptr != tcpSocket) {
        tcpSocket->disconnectFromHost();
        tcpSocket->deleteLater();
        tcpSocket = nullptr;
    }
}

void WinServer::slotReadData() {
    QByteArray arr = tcpSocket->readAll();
    arr.resize(3);
    qDebug() << "ctrl command " << arr << Qt::endl;
    if (arr == "110") {
        isOpenLed = true;
        slotCtrlLed();
        slotWriteData("success\r\n");
    } else if (arr == "111") {
        isOpenLed = false;
        slotCtrlLed();
        slotWriteData("success\r\n");
    } else if (arr == "210") {
        isOpenMach = true;
        slotCtrlMach();
        slotWriteData("success\r\n");
    } else if (arr == "211") {
        isOpenMach = false;
        slotCtrlMach();
        slotWriteData("success\r\n");
    } else {
        slotWriteData("fail\r\n");
    }
}

void WinServer::slotWriteData(const QString& message) const {
    tcpSocket->write(message.toLatin1());
}
