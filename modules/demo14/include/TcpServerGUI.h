#ifndef TCPRECEGUI_H
#define TCPRECEGUI_H

#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>
#include <QVBoxLayout>
#include <QWidget>

class TcpServerGUI : public QWidget {
  Q_OBJECT
public:
  explicit TcpServerGUI(QWidget *parent = nullptr);
  ~TcpServerGUI() noexcept override;
public slots:
  void slot_newConnection();
  void slot_closeConnection();
  void slot_sendData();
  void slot_recvData();

private:
  QListWidget *listWidget{};
  QLineEdit *lineEdit{};
  QTcpServer *tcpServer{};
  QTcpSocket *tcpSocket{};
};

#endif // TCPRECEGUI_H