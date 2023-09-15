#include "TcpClientGUI.h"

TcpClientGUI::TcpClientGUI(QWidget *parent) : QWidget(parent) {
  setWindowTitle("TcpClient");
  listWidget = new QListWidget;
  ipLineEdit = new QLineEdit;
  auto connect_button = new QPushButton("连接");
  connect(connect_button, SIGNAL(clicked(bool)), this,
          SLOT(slot_newConnection()));

  msgLineEdit = new QLineEdit;
  auto send_button = new QPushButton("发送");
  connect(send_button, SIGNAL(clicked(bool)), this, SLOT(slot_sendData()));

  auto gLayout = new QGridLayout(this);
  gLayout->addWidget(listWidget, 0, 0, 1, 2);
  gLayout->addWidget(ipLineEdit, 1, 0);
  gLayout->addWidget(connect_button, 1, 1);
  gLayout->addWidget(msgLineEdit, 2, 0);
  gLayout->addWidget(send_button, 2, 1);

  tcpSocket = new QTcpSocket(this);
  isConnect = false;
}

TcpClientGUI::~TcpClientGUI() noexcept {
  tcpSocket->disconnectFromHost();
  tcpSocket->close();
  tcpSocket->deleteLater();
}

void TcpClientGUI::slot_newConnection() {
  // 1.获取ip
  auto ipStr = ipLineEdit->text();
  if (!ipStr.trimmed().isEmpty()) {
    // 2.连接服务器
    connect(tcpSocket, SIGNAL(connected()), this, SLOT(slot_connected()));
    tcpSocket->connectToHost(QHostAddress(ipStr), 10000);
  }
}

void TcpClientGUI::slot_connected() {
  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(slot_recvData()));
  // 3.设置连接状态isConnect
  isConnect = true;
  // 4.保存连接记录
  auto ipStr = tcpSocket->peerAddress().toString();
  auto text = "connect to " + ipStr + " " +
              QTime::currentTime().toString("hh:mm") + " successfully\n";
  listWidget->addItem(text);
  listWidget->setCurrentRow(listWidget->count() - 1);
}

void TcpClientGUI::slot_sendData() {
  // 1.获取待发送数据
  auto msg = msgLineEdit->text();
  if (isConnect && !msg.trimmed().isEmpty()) {
    // 2.发送数据
    tcpSocket->write(msg.toLatin1());
    // 3.保存发送记录
    auto text = "send : " + ipLineEdit->text() + " " +
                QTime::currentTime().toString("hh:mm") + "\n" + msg;
    listWidget->addItem(text);
    listWidget->setCurrentRow(listWidget->count() - 1);
    // 4.清空输入框
    msgLineEdit->clear();
  }
}

void TcpClientGUI::slot_recvData() {
  // 1.接收数据
  auto array = tcpSocket->readAll();
  // 2.保存数据
  auto text = "recv : " + ipLineEdit->text() + " " +
              QTime::currentTime().toString("hh:mm") + "\n" + array;
  listWidget->addItem(text);
  listWidget->setCurrentRow(listWidget->count() - 1);
}