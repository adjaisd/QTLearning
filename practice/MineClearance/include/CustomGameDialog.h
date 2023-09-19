// 自定义游戏类
#ifndef CUSTOMGAMEDIALOG_H
#define CUSTOMGAMEDIALOG_H

#include "common.h"
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QSpinBox>
#include <QWidget>

class CustomGameDialog : public QDialog {
  Q_OBJECT
public:
  explicit CustomGameDialog(QWidget *parent = nullptr);

  void readSettings();  // 读自定义游戏设置文件
  void writeSettings(); // 写自定义游戏设置文件

public slots:
  // 接收确定按钮的槽(slots:)
  void slot_acceptOk();

signals:
  // 发送自定义游戏行，列，雷数的信号(signals)
  void signal_sendCustomSet(int, int, int);

private:
  QSpinBox *colSpinBox{};     // 列分量框
  QSpinBox *rowSpinBox{};     // 行分量框
  QSpinBox *mineNumSpinBox{}; // 雷数分量框
};

#endif // CUSTOMGAMEDIALOG_H
