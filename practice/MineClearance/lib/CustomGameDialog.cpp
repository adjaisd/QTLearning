#include "CustomGameDialog.h"

/*
函数功能：构造自定义游戏类界面，连接信号与槽
函数流程：
创建界面
创建按钮并连接信号到本类的相应槽
读取原来自定义游戏设置
 */
CustomGameDialog::CustomGameDialog(QWidget *parent) : QDialog(parent) {
  setWindowTitle("自定义游戏");
  setWindowIcon(QIcon(iconImagePath));

  // label
  auto col_label = new QLabel(tr("自定义列数"));
  auto row_label = new QLabel(tr("自定义行数"));
  auto mineNum_label = new QLabel(tr("自定义雷数"));

  // 计数器
  rowSpinBox = new QSpinBox(this);
  colSpinBox = new QSpinBox(this);
  mineNumSpinBox = new QSpinBox(this);

  rowSpinBox->setRange(LOWROWANDCOL, HIGHROW);
  colSpinBox->setRange(LOWROWANDCOL, HIGHCOL);
  mineNumSpinBox->setRange(LOWMINENUM, HIGHMINENUM);
  // 动态改变雷数的上限
  connect(rowSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [&](int val) {
            qDebug() << "row当前值：" + QString::number(val);
            int nxt = colSpinBox->value() * val / 2;
            nxt = (nxt > HIGHMINENUM) ? HIGHMINENUM : nxt;
            qDebug() << "最大值：" + QString::number(nxt);
            mineNumSpinBox->setRange(LOWMINENUM, nxt);
          });
  connect(colSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this,
          [&](int val) {
            qDebug() << "col当前值：" + QString::number(val);
            int nxt = rowSpinBox->value() * val / 2;
            nxt = (nxt > HIGHMINENUM) ? HIGHMINENUM : nxt;
            qDebug() << "最大值：" + QString::number(nxt);
            mineNumSpinBox->setRange(LOWMINENUM, nxt);
          });

  rowSpinBox->setSingleStep(1);
  colSpinBox->setSingleStep(1);
  mineNumSpinBox->setSingleStep(1);

  // button
  auto ok_button = new QPushButton(tr("确定"));
  auto cancel_button = new QPushButton(tr("取消"));

  // slot
  connect(ok_button, SIGNAL(clicked(bool)), this, SLOT(slot_acceptOk()));
  connect(cancel_button, SIGNAL(clicked(bool)), this, SLOT(close()));

  // layout
  auto hLayout = new QHBoxLayout;
  hLayout->addStretch();
  hLayout->addWidget(ok_button);
  hLayout->addWidget(cancel_button);

  auto gLayout = new QGridLayout(this);
  gLayout->addWidget(row_label, 0, 0);
  gLayout->addWidget(col_label, 1, 0);
  gLayout->addWidget(mineNum_label, 2, 0);
  gLayout->addWidget(rowSpinBox, 0, 1);
  gLayout->addWidget(colSpinBox, 1, 1);
  gLayout->addWidget(mineNumSpinBox, 2, 1);
  gLayout->addLayout(hLayout, 3, 0, 1, 2);

  readSettings();
}

/*
函数功能：读自定义游戏设置文件，并将读取到的数据设置到相应分量框
函数流程：
读取自定义游戏设置
将读取到的数据设置到相应分量框
 */
void CustomGameDialog::readSettings() {
  auto settings = new QSettings(orgName, appName, this);
  // 1.获取数据: 行、列、雷数量
  settings->beginGroup(gameLevelGroupPrefix);
  auto row = settings->value("row", LOWROWANDCOL).toInt();
  auto col = settings->value("col", LOWROWANDCOL).toInt();
  auto mineNum = settings->value("mineNum", LOWMINENUM).toInt();
  settings->endGroup();
  // 2.更新数据
  rowSpinBox->setValue(row);
  colSpinBox->setValue(col);
  mineNumSpinBox->setValue(mineNum);
}

/*
函数功能：写自定义游戏设置文件，将当前的自定义游戏设置保存到注册表
 */
void CustomGameDialog::writeSettings() {
  auto settings = new QSettings(orgName, appName, this);
  settings->beginGroup(gameLevelGroupPrefix);
  settings->setValue("row", rowSpinBox->value());
  settings->setValue("col", colSpinBox->value());
  settings->setValue("mineNum", mineNumSpinBox->value());
  settings->endGroup();
}

/*
函数功能：接收确定按钮的槽
函数流程：
获取分量框中的数据
发送自定义游戏数据信号，将当前设置保存到注册表，关闭对话框
 */
void CustomGameDialog::slot_acceptOk() {
  writeSettings();
  // 发送自定义游戏信号
  emit signal_sendCustomSet(rowSpinBox->value(), colSpinBox->value(),
                            mineNumSpinBox->value());
  close();
}