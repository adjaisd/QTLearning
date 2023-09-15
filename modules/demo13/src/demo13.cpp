#include <QApplication>
#include <QHostInfo>
#include <QNetworkInterface>
#include "UdpReceGUI.h"
#include "UdpSendGUI.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
#if 0
  // 获取本地主机名
  auto localHostName = QHostInfo::localHostName();
  qDebug() << "hostname ; " << localHostName << Qt::endl;
  // 获取ip列表
  auto hostInfo = QHostInfo::fromName(localHostName);
  auto list = hostInfo.addresses();
  std::for_each(list.begin(), list.end(),
                [](const auto &ip) { qDebug() << "ip : " << ip << Qt::endl; });
  // 网卡
  qDebug() << "network card" << QNetworkInterface::allInterfaces() << Qt::endl;
  // mac
  auto networkInf = new QNetworkInterface();
  auto interfaces = QNetworkInterface::allInterfaces();
  for (const auto &inter : interfaces) {
    qDebug() << "name : " << inter.name() << Qt::endl;
    qDebug() << "mac  : " << inter.hardwareAddress() << Qt::endl;
    for (const auto &item : inter.addressEntries()) {
      qDebug() << "ip  : " << item.ip() << Qt::endl;
    }
  }
  qDebug() << "mac : " << networkInf->hardwareAddress() << Qt::endl;
  qDebug() << "name: " << networkInf->name() << Qt::endl;
  qDebug() << "ip : " << (new QNetworkAddressEntry)->ip() << Qt::endl;
#else
  UdpReceGUI udpReceGui;
  UdpSendGUI udpSendGui;
  udpReceGui.show();
  udpSendGui.show();
#endif
  return a.exec();
}
