#include "UdpSendGUI.h"

UdpSendGUI::UdpSendGUI(QWidget *parent) : QWidget(parent) {
  setWindowTitle("UDP发送");
  auto label = new QLabel("消息");
  lineEdit = new QLineEdit;
  auto send_button = new QPushButton("发送");
  connect(send_button, SIGNAL(clicked(bool)), this, SLOT(slot_sendData()));

  auto hLayout = new QHBoxLayout(this);
  hLayout->addWidget(label);
  hLayout->addWidget(lineEdit);
  hLayout->addWidget(send_button);

  // 2.创建udp套接字
  udpSocket = new QUdpSocket(this);
}

UdpSendGUI::~UdpSendGUI() noexcept {
  udpSocket->close();
  udpSocket->deleteLater();
}

void UdpSendGUI::slot_sendData() {
  // 1.获取单行文本
  auto text = lineEdit->text();
  if (!text.trimmed().isEmpty()) {
    // 2.发送数据
#define sendChoice 3
#if sendChoice == 1
    // 广播发送
    qDebug() << "广播发送" << Qt::endl;
    udpSocket->writeDatagram(text.toLatin1(), QHostAddress::Broadcast, 10000);
#elif sendChoice == 2
    // 单播发送
    qDebug() << "单播发送" << Qt::endl;
    udpSocket->writeDatagram(text.toUtf8(), QHostAddress("192.168.30.1"),
                             10000);
#else
    // 组播发送
    qDebug() << "组播发送" << Qt::endl;
    udpSocket->writeDatagram(text.toUtf8(), QHostAddress("239.1.2.3"), 10000);
#endif
    lineEdit->clear();
  }
}