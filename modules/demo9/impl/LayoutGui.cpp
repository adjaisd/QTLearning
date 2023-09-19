#include "LayoutGui.h"

LayoutGui::LayoutGui(QWidget *parent) : QWidget(parent) {
  setWindowTitle("layoutGui示例");
  // 上部分左边布局
  // 姓名
  auto name_label = new QLabel("姓名");
  auto name_edit = new QLineEdit;

  // 性别
  auto sex_label = new QLabel("性别");
  auto sex_radio_1 = new QRadioButton("男");
  auto sex_radio_2 = new QRadioButton("女");
  sex_radio_1->setCheckable(true); // 可选中
  sex_radio_2->setCheckable(true);
  sex_radio_1->setChecked(true); // 默认选中

  // 性别的单选按钮为一组
  auto sex_group = new QButtonGroup;
  sex_group->addButton(sex_radio_1);
  sex_group->addButton(sex_radio_2);

  // 布局
  auto sex_layout = new QHBoxLayout;
  sex_layout->addWidget(sex_radio_1);
  sex_layout->addWidget(sex_radio_2);
  sex_layout->addStretch();

  // 年龄
  auto age_label = new QLabel("年龄");
  auto age_spinBox = new QSpinBox;
  age_spinBox->setRange(1, 100);
  age_spinBox->setSingleStep(1);
  age_spinBox->setValue(18);

  // 生日
  auto birthDate_label = new QLabel("生日");
  auto birthDate_edit = new QDateEdit;
  birthDate_edit->setDisplayFormat("yyyy-MM-dd");
  // 日历自动弹出
  birthDate_edit->setCalendarPopup(true);
  birthDate_edit->setDate(QDate::currentDate());

  // 学历
  auto degree_label = new QLabel("学历");
  auto degree_comboBox = new QComboBox;
  degree_comboBox->addItem("高中");
  degree_comboBox->addItem("大专");
  degree_comboBox->addItem("本科");
  degree_comboBox->addItem("硕士");

  // 爱好
  auto hobby_label = new QLabel("爱好");
  auto hobby_checkBox_1 = new QCheckBox("游泳");
  auto hobby_checkBox_2 = new QCheckBox("足球");
  auto hobby_checkBox_3 = new QCheckBox("篮球");

  // 可选
  hobby_checkBox_1->setCheckable(true);
  hobby_checkBox_2->setCheckable(true);
  hobby_checkBox_3->setCheckable(true);

  // 默认选中
  hobby_checkBox_1->setChecked(true);

  // 布局
  auto hobby_qhBoxLayout = new QHBoxLayout;
  hobby_qhBoxLayout->addWidget(hobby_checkBox_1);
  hobby_qhBoxLayout->addWidget(hobby_checkBox_2);
  hobby_qhBoxLayout->addWidget(hobby_checkBox_3);

  // 详细资料
  auto detail_label = new QLabel("详细资料");
  detail_label->setAlignment(Qt::AlignTop);
  auto detail_edit = new QTextEdit;
  auto mark_label = new QLabel("备注");
  mark_label->setFrameStyle(QFrame::Panel | QFrame::Sunken); // 下沉

  auto left_gridLayout = new QGridLayout;
  left_gridLayout->addWidget(name_label, 0, 0);
  left_gridLayout->addWidget(name_edit, 0, 1);
  left_gridLayout->addWidget(sex_label, 1, 0);
  left_gridLayout->addLayout(sex_layout, 1, 1);

  left_gridLayout->addWidget(age_label, 2, 0);
  left_gridLayout->addWidget(age_spinBox, 2, 1);

  left_gridLayout->addWidget(birthDate_label, 3, 0);
  left_gridLayout->addWidget(birthDate_edit, 3, 1);

  left_gridLayout->addWidget(degree_label, 3, 0);
  left_gridLayout->addWidget(degree_comboBox, 4, 1);

  left_gridLayout->addWidget(hobby_label, 5, 0);
  left_gridLayout->addLayout(hobby_qhBoxLayout, 5, 1);

  left_gridLayout->addWidget(detail_label, 6, 0);
  left_gridLayout->addWidget(detail_edit, 6, 1);

  left_gridLayout->addWidget(mark_label, 7, 0, 1, 2);

  // 上部分右边布局
  // 头像
  auto avatar_label = new QLabel("头像");
  avatar = new QLabel;
  avatar->setPixmap(QPixmap(":/images/3.png"));

  auto avatar_button = new QPushButton("修改头像");

  connect(avatar_button, SIGNAL(clicked(bool)), this, SLOT(slot_changeHead()));

  auto avatar_hLayout = new QHBoxLayout;
  avatar_hLayout->addWidget(avatar);
  avatar_hLayout->addWidget(avatar_label);
  avatar_hLayout->addWidget(avatar_button);

  // 介绍
  auto intro_label = new QLabel("介绍");
  auto intro_edit = new QTextEdit;

  auto right_layout = new QVBoxLayout;
  right_layout->addLayout(avatar_hLayout);
  right_layout->addWidget(intro_label);
  right_layout->addWidget(intro_edit);

  // 整合上部分左右布局
  auto up_hLayout = new QHBoxLayout;
  up_hLayout->addLayout(left_gridLayout);
  up_hLayout->addLayout(right_layout);

  // 下部分
  auto ok_button = new QPushButton("确认");
  auto cancel_button = new QPushButton("取消");
  auto down_hLayout = new QHBoxLayout;
  down_hLayout->addStretch();
  down_hLayout->addWidget(ok_button);
  down_hLayout->addWidget(cancel_button);

  // 整合上下部分
  auto main_layout = new QVBoxLayout(this);
  main_layout->addLayout(up_hLayout);
  main_layout->addLayout(down_hLayout);
}

LayoutGui::~LayoutGui() noexcept = default;

void LayoutGui::slot_changeHead() {
  auto path =
      QFileDialog::getOpenFileName(this, "选择头像", "../../", "头像(*.png)");
  if (!path.trimmed().isEmpty()) {
    avatar->setPixmap(QPixmap(path));
  }
}
