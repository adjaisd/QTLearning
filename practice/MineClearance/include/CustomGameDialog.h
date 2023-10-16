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

/*
 * Class:       CustomGameDialog
 * Description: 自定义游戏对话窗口类
 * Author:      TheOne1221
 * Version:     1.0.0
 * Date:        2023.9.20
 */
class CustomGameDialog : public QDialog {
  Q_OBJECT
public:
  /*
   * Function:    CustomGameDialog
   * Description: 自定义窗口构造函数，用于初始化对话窗口
   * Param:       parent
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  explicit CustomGameDialog(QWidget *parent = nullptr);
  /*
   * Function:    readSettings
   * Description: 读自定义游戏设置文件
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void readSettings();
  /*
   * Function:    writeSettings
   * Description: 写自定义游戏设置文件
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void writeSettings();

public slots:
  /*
   * Function:    slot_acceptOk
   * Description: 接收确定按钮的槽
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void slot_acceptOk();

signals:
  void signal_sendCustomSet(int, int, int); // 发送自定义游戏行，列，雷数的信号

private:
  QSpinBox *colSpinBox{};     // 列分量框
  QSpinBox *rowSpinBox{};     // 行分量框
  QSpinBox *mineNumSpinBox{}; // 雷数分量框
};

#endif // CUSTOMGAMEDIALOG_H