#include "HeroDialog.h"

/*
函数功能：初始化主要的数据成员，创建相应的界面组件，创建主程序界面
函数流程：
创建界面
创建按钮并连接信号到本类的相应槽
读取旧数据并显示
 */
HeroDialog::HeroDialog(QWidget *parent) : QDialog(parent) {
  setWindowTitle("扫雷英雄榜");
  setWindowIcon(QIcon(iconImagePath));

  // label
  auto lowLevel_label = new QLabel(tr("初级"));
  auto middleLevel_label = new QLabel(tr("中级"));
  auto highLevel_label = new QLabel(tr("高级"));

  lowRecordTimeLabel = new QLabel;
  middleRecordTimeLabel = new QLabel;
  highRecordTimeLabel = new QLabel;

  lowRecordNameLabel = new QLabel;
  middleRecordNameLabel = new QLabel;
  highRecordNameLabel = new QLabel;

  // button
  auto reset_button = new QPushButton(tr("重置"));
  auto ok_button = new QPushButton(tr("确定"));

  // slot
  connect(reset_button, SIGNAL(clicked(bool)), this, SLOT(slot_reset()));
  connect(ok_button, SIGNAL(clicked(bool)), this, SLOT(close()));

  // layout
  auto main_hLayout = new QVBoxLayout(this);
  auto up_gLayout = new QGridLayout;
  auto down_hLayout = new QHBoxLayout;

  up_gLayout->addWidget(lowLevel_label, 0, 0);
  up_gLayout->addWidget(middleLevel_label, 1, 0);
  up_gLayout->addWidget(highLevel_label, 2, 0);

  up_gLayout->addWidget(lowRecordTimeLabel, 0, 1);
  up_gLayout->addWidget(middleRecordTimeLabel, 1, 1);
  up_gLayout->addWidget(highRecordTimeLabel, 2, 1);

  up_gLayout->addWidget(lowRecordNameLabel, 0, 2);
  up_gLayout->addWidget(middleRecordNameLabel, 1, 2);
  up_gLayout->addWidget(highRecordNameLabel, 2, 2);

  down_hLayout->addWidget(reset_button);
  down_hLayout->addWidget(ok_button);
  down_hLayout->setAlignment(Qt::AlignCenter);

  main_hLayout->addLayout(up_gLayout);
  main_hLayout->addLayout(down_hLayout);

  // 初始化
  init_heroRecord();
  readSettings();
}

/*
函数功能：读英雄榜数据并设置到当前界面
 */
void HeroDialog::readSettings() {
  auto settings = new QSettings("MineOrg", "MineClearance", this);

  // 1.获取数据: 行、列、雷数量
  settings->beginGroup("hero");
  auto low_time = settings->value("low_time", 999).toInt();
  auto middle_time = settings->value("middle_time", 999).toInt();
  auto high_time = settings->value("high_time", 999).toInt();

  auto low_name = settings->value("low_name", "匿名").toString();
  auto middle_name = settings->value("middle_name", "匿名").toString();
  auto high_name = settings->value("high_name", "匿名").toString();
  settings->endGroup();

  // 2.更新数据
  lowRecordTimeLabel->setText(QString().setNum(low_time));
  middleRecordTimeLabel->setText(QString().setNum(middle_time));
  highRecordTimeLabel->setText(QString().setNum(high_time));

  lowRecordNameLabel->setText(low_name);
  middleRecordNameLabel->setText(middle_name);
  highRecordNameLabel->setText(high_name);
}

/*
函数功能：初始化英雄榜数据到注册表
 */
void HeroDialog::init_heroRecord() {
  lowRecordTimeLabel->setText(QString().setNum(999));
  middleRecordTimeLabel->setText(QString().setNum(999));
  highRecordTimeLabel->setText(QString().setNum(999));

  lowRecordNameLabel->setText("匿名");
  middleRecordNameLabel->setText("匿名");
  highRecordNameLabel->setText("匿名");
}

/*
函数功能：
函数流程：
重新设置英雄榜的槽
初始化英雄榜
 */
void HeroDialog::slot_reset() {
  auto settings = new QSettings("MineOrg", "MineClearance", this);
  settings->beginGroup("hero");
  settings->setValue("low_time", 999);
  settings->setValue("middle_time", 999);
  settings->setValue("high_time", 999);

  settings->setValue("low_name", "匿名");
  settings->setValue("middle_name", "匿名");
  settings->setValue("high_name", "匿名");
  settings->endGroup();

  // 2. 提示并重新载入
  QMessageBox::information(this, "reset successfully", "重置成功",
                           QMessageBox::Ok);
  init_heroRecord();
  readSettings();
}