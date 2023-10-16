#ifndef HERODIALOG_H
#define HERODIALOG_H

#include "common.h"
#include <QDialog>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>

/*
 * Class:       HeroDialog
 * Description: 英雄榜窗口类
 * Author:      TheOne1221
 * Version:     1.0.0
 * Date:        2023.9.20
 */
class HeroDialog : public QDialog {
  Q_OBJECT
public:
  /*
   * Function:    HeroDialog
   * Description: 英雄榜窗口构造函数
   * Param:       parent
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  explicit HeroDialog(QWidget *parent = nullptr);
  /*
   * Function:    readSettings
   * Description: 读英雄榜数据
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void readSettings();
  /*
   * Function:    init_heroRecord
   * Description: 初始化英雄榜数据
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void init_heroRecord();

public slots:
  /*
   * Function:    slot_reset
   * Description: 重新设置英雄榜数据槽
   * Param:       无
   * Return:      void
   * Author:      TheOne1221
   * Version:     1.0.0
   * Date:        2023.9.20
   */
  void slot_reset();

private:
  QLabel *lowRecordTimeLabel{};    // 初级纪录时间
  QLabel *middleRecordTimeLabel{}; // 中级纪录时间
  QLabel *highRecordTimeLabel{};   // 高级纪录时间
  QLabel *lowRecordNameLabel{};    // 初级纪录姓名
  QLabel *middleRecordNameLabel{}; // 中级纪录姓名
  QLabel *highRecordNameLabel{};   // 高级纪录姓名
};

#endif // HERODIALOG_H