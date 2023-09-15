#ifndef TCPSENDGUI_H
#define TCPSENDGUI_H

#include <QHostAddress>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QTcpSocket>
#include <QGridLayout>
#include <QTime>
#include <QWidget>

class TcpClientGUI : public QWidget {
  Q_OBJECT
public:
  explicit TcpClientGUI(QWidget *parent = nullptr);
  ~TcpClientGUI() noexcept override;

public slots:
  void slot_newConnection();
  void slot_connected();
  void slot_sendData();
  void slot_recvData();

private:
  QListWidget *listWidget{};
  QLineEdit *ipLineEdit{};
  QLineEdit *msgLineEdit{};
  QTcpSocket *tcpSocket{};
  bool isConnect{};
};

#endif // TCPSENDGUI_H