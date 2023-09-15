#include <QApplication>
#include "TcpServerGUI.h"
#include "TcpClientGUI.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  TcpServerGUI tcpServerGui;
  TcpClientGUI tcpClientGui;
  tcpServerGui.show();
  tcpClientGui.show();
  return a.exec();
}