#include "SettingsGui.h"

SettingsGui::SettingsGui(QWidget *parent) : QWidget(parent) {
  setWindowTitle("SettingsGui");
  setFixedSize(500, 300);

  label = new QLabel("Settings");
  textEdit = new QTextEdit;
  auto color_button = new QPushButton("选择颜色");
  connect(color_button, SIGNAL(clicked(bool)), this, SLOT(slot_changeColor()));

  auto vLayout = new QVBoxLayout(this);
  vLayout->addWidget(label);
  vLayout->addWidget(color_button);
  vLayout->addWidget(textEdit);

  readSettings();
}

SettingsGui::~SettingsGui() noexcept = default;

void SettingsGui::writeSettings() {
  // 1.创建QSettings对象
  auto settings = new QSettings("DEMO16", "SettingsDemo", this);
  // 2.开始组
  settings->beginGroup("pos_size");
  // 3.调用setValue()
  settings->setValue("pos", pos());
  settings->setValue("size", frameSize());
  // 4.关闭组
  settings->endGroup();

  settings->beginGroup("string_color");
  settings->setValue("string", textEdit->toPlainText());
  settings->setValue("color", label->palette().color(QPalette::WindowText));
  settings->endGroup();
}

void SettingsGui::readSettings() {
  // 1.获取数据
  auto *settings = new QSettings("DEMO16", "SettingsDemo", this);
  settings->beginGroup("pos_size");
  auto pos = settings->value("pos", QPoint(50, 50)).toPoint();
  auto size = settings->value("size", QSize(100, 50)).toSize();
  settings->endGroup();

  // 2.使用数据设置窗口
  move(pos);
  resize(size);

  settings->beginGroup("string_color");
  auto str = settings->value("string", "no string").toString();
  auto color = settings->value("color", QColor(255, 0, 0)).value<QColor>();
  settings->endGroup();

  textEdit->append(str);
  auto pale = label->palette();
  pale.setColor(QPalette::WindowText, color);
  label->setPalette(pale);
}

void SettingsGui::closeEvent(QCloseEvent *event) { writeSettings(); }

void SettingsGui::slot_changeColor() {
  auto color = QColorDialog::getColor(Qt::blue, this);
  if (color.isValid()) {
    auto pale = label->palette();
    pale.setColor(QPalette::WindowText, color);
    label->setPalette(pale);
  }
}