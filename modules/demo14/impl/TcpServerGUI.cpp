#include "TcpServerGUI.h"

TcpServerGUI::TcpServerGUI(QWidget *parent) : QWidget(parent) {
  setWindowTitle("TcpServer");

  // 1.创建界面
  listWidget = new QListWidget;
  lineEdit = new QLineEdit;
  auto send_button = new QPushButton("发送");
  connect(send_button, SIGNAL(clicked(bool)), this, SLOT(slot_sendData()));

  auto vLayout = new QVBoxLayout(this);
  vLayout->addWidget(listWidget);
  vLayout->addWidget(lineEdit);
  vLayout->addWidget(send_button);

  // 2.创建tcpserver，并且监听
  tcpServer = new QTcpServer(this);
  if (!tcpServer->listen(QHostAddress("192.168.30.1"), 10000)) {
    QMessageBox::critical(this, "绑定失败", "绑定失败:IP错误或端口已绑定");
    close();
  }

  connect(tcpServer, SIGNAL(newConnection()), this, SLOT(slot_newConnection()));

  // 3.创建socket
  tcpSocket = nullptr;
}

TcpServerGUI::~TcpServerGUI() noexcept {
  tcpServer->close();
  tcpServer->deleteLater();
}

void TcpServerGUI::slot_newConnection() {
  QHostAddress clientAddr;
  ushort clientPort;
  if (tcpServer->hasPendingConnections()) {
    tcpSocket = tcpServer->nextPendingConnection();
    // 读取槽函数
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(slot_recvData()));
    // 断开槽函数
    connect(tcpSocket, SIGNAL(disconnected()), this,
            SLOT(slot_closeConnection()));
    clientAddr = tcpSocket->peerAddress(); // 获取客户端ip
    clientPort = tcpSocket->peerPort();    // 获取客户端port
    auto text = clientAddr.toString() + " : " + QString::number(clientPort) +
                " " + QTime::currentTime().toString("hh:mm") + " connected";
    listWidget->addItem(text); // 信息添加到listWidget
    listWidget->setCurrentRow(listWidget->count() - 1); // 移动光标为当前行
  }
}

void TcpServerGUI::slot_closeConnection() {
  QHostAddress clientAddr = tcpSocket->peerAddress();
  auto text = clientAddr.toString() + " " +
              QTime::currentTime().toString("hh:mm") + " disconnected\n";
  listWidget->addItem(text);
  listWidget->setCurrentRow(listWidget->count() - 1);

  tcpSocket->close();       // 关闭服务端tcpSocket
  tcpSocket->deleteLater(); // 释放tcpSocket
}

void TcpServerGUI::slot_sendData() {
  auto msg = lineEdit->text();
  QHostAddress clientAddr;
  if (tcpSocket != nullptr && !msg.trimmed().isEmpty()) {
    // 1.发送数据
    tcpSocket->write(msg.toLatin1());
    // 2.将数据保存到listWidget
    clientAddr = tcpSocket->peerAddress();
    auto text = "send : " + clientAddr.toString() + " " +
                QTime::currentTime().toString("hh:mm") + "\n" + msg;
    listWidget->addItem(text);
    listWidget->setCurrentRow(listWidget->count() - 1);
    // 3.清空文本框
    lineEdit->clear();
  }
}

void TcpServerGUI::slot_recvData() {
  // 1.接收数据
  auto array = tcpSocket->readAll();
  // 2.将数据保存到listWidget
  QHostAddress clientAddr = tcpSocket->peerAddress();
  auto text = "recv : " + clientAddr.toString() + " " +
              QTime::currentTime().toString("hh:mm") + "\n" + array;
  listWidget->addItem(text);
  listWidget->setCurrentRow(listWidget->count() - 1);
}