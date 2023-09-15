#ifndef UDPSENDGUI_H
#define UDPSENDGUI_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QUdpSocket>
#include <QWidget>

class UdpSendGUI : public QWidget {
  Q_OBJECT
public:
  explicit UdpSendGUI(QWidget *parent = nullptr);
  ~UdpSendGUI() noexcept override;

public slots:
  void slot_sendData();

private:
  QLineEdit *lineEdit;
  QUdpSocket *udpSocket;
};

#endif // UDPSENDGUI_H