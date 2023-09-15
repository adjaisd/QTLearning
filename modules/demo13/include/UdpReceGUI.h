#ifndef UDPRECEGUI_H
#define UDPRECEGUI_H

#include <QDebug>
#include <QHostAddress>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QUdpSocket>
#include <QWidget>

class UdpReceGUI : public QWidget {
  Q_OBJECT
public:
  explicit UdpReceGUI(QWidget *parent = nullptr);
  ~UdpReceGUI() noexcept override;

public slots:
  void slot_receData();

private:
  QLabel *messageLabel;
  QUdpSocket *udpSocket;
};

#endif // UDPRECEGUI_H