#ifndef WINSERVER_H
#define WINSERVER_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QGridLayout>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class WinServer; }
QT_END_NAMESPACE

class WinServer : public QWidget {
Q_OBJECT

public:
    explicit WinServer(QWidget *parent = nullptr);

    ~WinServer() override;

    enum iconSize {
        WIDTH = 48,
        HEIGHT = 48
    };
    bool isOpenLed;
    bool isOpenMach;

    QPushButton *ledImgButton;  // 厨房灯img按钮
    QPushButton *ledCtrlButton; // 厨房灯控制按钮
    QPushButton *machImgButton; // 油烟机img按钮
    QPushButton *machCtrlButton;// 油烟机控制按钮

    QTcpSocket *tcpSocket;
    QTcpServer *tcpServer;

public slots:
    void slotCtrlLed();
    void slotCtrlMach();
    void slotNewConnection();
    void slotDisconnection();
    void slotReadData();
    void slotWriteData(const QString&) const;

private:
    Ui::WinServer *ui;
};

#endif //WINSERVER_H
