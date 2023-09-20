// 英雄榜类
#ifndef HERODIALOG_H
#define HERODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QVBoxLayout>
#include <QMessageBox>
#include "common.h"

class  HeroDialog : public QDialog {
  Q_OBJECT
public:
  explicit HeroDialog(QWidget *parent = nullptr);

  void readSettings();    // 读英雄榜数据
  void init_heroRecord(); // 初始化英雄榜数据

public slots:
  void slot_reset(); // 重新设置英雄榜数据槽(slots:)

private:
  QLabel *lowRecordTimeLabel{};    // 初级纪录时间
  QLabel *middleRecordTimeLabel{}; // 中级纪录时间
  QLabel *highRecordTimeLabel{};   // 高级纪录时间
  QLabel *lowRecordNameLabel{};    // 初级纪录姓名
  QLabel *middleRecordNameLabel{}; // 中级纪录姓名
  QLabel *highRecordNameLabel{};   // 高级纪录姓名
};

#endif // HERODIALOG_H
