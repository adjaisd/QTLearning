#include "UdpReceGUI.h"
#include <QVBoxLayout>

UdpReceGUI::UdpReceGUI(QWidget *parent) : QWidget(parent) {
  setWindowTitle("UDP接受示例");
  resize(300, 100);

  // 1.创建界面
  messageLabel = new QLabel("消息");
  messageLabel->setAlignment(Qt::AlignCenter);
  auto close_button = new QPushButton("关闭");
  connect(close_button, SIGNAL(clicked(bool)), this, SLOT(close()));

  auto vLayout = new QVBoxLayout(this);
  vLayout->addWidget(messageLabel);
  vLayout->addWidget(close_button);

  // 2.创建udp套接字
  udpSocket = new QUdpSocket(this);
#define receChoice 3
#if receChoice == 1
  // 1.广播接收
  qDebug() << "广播接收" << Qt::endl;
  if (!udpSocket->bind(10000, QUdpSocket::ShareAddress)) {
    QMessageBox::critical(this, "绑定失败", "绑定失败:IP错误或端口已绑定",
                          QMessageBox::Ok);
    close();
  }
#elif receChoice == 2
  // 2.单播接收
  qDebug() << "单播接收" << Qt::endl;
  if (!udpSocket->bind(QHostAddress("192.168.30.1"), 10000)) {
    QMessageBox::critical(this, "绑定失败", "绑定失败:IP错误或端口已绑定",
                          QMessageBox::Ok);
    close();
  }
#else
  // 3.组播接收
  qDebug() << "组播接收" << Qt::endl;
  if (!udpSocket->bind(QHostAddress("192.168.30.1"), 10000)) {
    QMessageBox::critical(this, "绑定失败", "绑定失败:IP错误或端口已绑定",
                          QMessageBox::Ok);
    close();
  }
  if (!udpSocket->joinMulticastGroup(QHostAddress("239.1.2.3"))) {
    QMessageBox::critical(this, "绑定失败", "组播绑定失败", QMessageBox::Ok);
    close();
  }
#endif

  connect(udpSocket, SIGNAL(readyRead()), this, SLOT(slot_receData()));
}

UdpReceGUI::~UdpReceGUI() noexcept {
  udpSocket->close();
  udpSocket->deleteLater();
}

void UdpReceGUI::slot_receData() {
  QHostAddress addr;
  ushort port;
  QString text;
  if (udpSocket->hasPendingDatagrams()) {
    // 1.建立QByteArray对象
    QByteArray array;
    auto size = udpSocket->pendingDatagramSize();
    array.resize(size);
    // 2.接收数据
    udpSocket->readDatagram(array.data(), size, &addr, &port);
    // 3.显示数据
    text = "receive : " + addr.toString() + " " + QString::number(port) + " " +
           QString::fromUtf8(array);
    messageLabel->setText(text);
  }
}