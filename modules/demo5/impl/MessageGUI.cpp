#include "MessageGUI.h"

MessageGUI::MessageGUI(QWidget *parent) : QDialog(parent) {
  // 国际化处理
  setWindowTitle("MessageDialog示例");

  message_label = new QLabel;
  message_label->setAlignment(Qt::AlignCenter); // 居中显示

  auto *question_button = new QPushButton("question");
  auto *information_button = new QPushButton("information");
  auto *warning_button = new QPushButton("warning");
  auto *critical_button = new QPushButton("critical");
  auto *about_button = new QPushButton("about_button");
  auto *aboutQt_button = new QPushButton("aboutQt");
  auto *custom_button = new QPushButton("custom");

  // 垂直布局
  auto *gridLayout = new QGridLayout;
  gridLayout->addWidget(question_button, 0, 0);
  gridLayout->addWidget(information_button, 0, 1);
  gridLayout->addWidget(warning_button, 1, 0);
  gridLayout->addWidget(critical_button, 1, 1);
  gridLayout->addWidget(about_button, 2, 0);
  gridLayout->addWidget(aboutQt_button, 2, 1);
  gridLayout->addWidget(custom_button, 3, 0);

  auto *verticalLayout = new QVBoxLayout;
  verticalLayout->addWidget(message_label);
  verticalLayout->addLayout(gridLayout);

  //  setLayout(gridLayout);
  setLayout(verticalLayout);

  connect(question_button, SIGNAL(clicked(bool)), this, SLOT(slot_question()));
  connect(information_button, SIGNAL(clicked(bool)), this,
          SLOT(slot_information()));
  connect(warning_button, SIGNAL(clicked(bool)), this, SLOT(slot_warning()));
  connect(critical_button, SIGNAL(clicked(bool)), this, SLOT(slot_critical()));
  connect(about_button, SIGNAL(clicked(bool)), this, SLOT(slot_about()));
  connect(aboutQt_button, SIGNAL(clicked(bool)), this, SLOT(slot_aboutQt()));
  connect(custom_button, SIGNAL(clicked(bool)), this, SLOT(slot_custom()));
}

MessageGUI::~MessageGUI() noexcept = default;

void MessageGUI::slot_question() {
  auto res = QMessageBox::question(this, tr("question message box"),
                                   tr("ip,192.168.1.1"), QMessageBox::Ok,
                                   QMessageBox::Cancel);
  if (res == QMessageBox::Ok)
    message_label->setText("question / ok");
  else if (res == QMessageBox::Cancel)
    message_label->setText("question /cancel");
}

void MessageGUI::slot_information() {
  auto res = QMessageBox::information(this, tr("information message box"),
                                      tr("ip, 192.168.1.1"), QMessageBox::Ok,
                                      QMessageBox::Cancel);
  if (res == QMessageBox::Ok)
    message_label->setText(tr("information / ok"));
}

void MessageGUI::slot_warning() {
  auto res = QMessageBox::warning(this, tr("warning message box"),
                                  tr("ip, 192.168.1.1"), QMessageBox::Ok,
                                  QMessageBox::Cancel);
  if (res == QMessageBox::Ok)
    message_label->setText(tr("warning / ok"));
  else if (res == QMessageBox::Discard)
    message_label->setText(tr("warning / discard"));
  else if (res == QMessageBox::Cancel)
    message_label->setText(tr("warning / cancel"));
}

void MessageGUI::slot_critical() {
  // 错误消息框
  auto res = QMessageBox::critical(this, tr("ip bind error"),
                                   tr("ip, 192.168.1.1"), QMessageBox::Ok);
  if (res == QMessageBox::Ok)
    message_label->setText(tr("critical / ok"));
}

void MessageGUI::slot_about() {
  auto text = tr("user : zhangsan\n") + tr("application name : message demo");
  QMessageBox::about(this, tr("about message box"), text);
  message_label->setText(tr("about message box"));
}

void MessageGUI::slot_aboutQt() {
  QMessageBox::aboutQt(this);
  message_label->setText(tr("aboutQT message box"));
}

void MessageGUI::slot_custom() {
  auto *custom = new QMessageBox(this);
  custom->setWindowTitle(tr("custom message box"));
  custom->setText(tr("this is custom message box"));
  custom->setIconPixmap(QPixmap(":/images/linuxredhat.png"));

  auto lock_button = custom->addButton(tr("lock"), QMessageBox::ActionRole);
  auto unlock_button = custom->addButton(tr("unlock"), QMessageBox::ActionRole);
  auto cancel_button = custom->addButton(QMessageBox::Cancel);

  custom->exec();

  // 获取用户单击的按钮
  auto click_button = custom->clickedButton();
  if (click_button == lock_button)
    message_label->setText(tr("custom / lock"));
  else if (click_button == unlock_button)
    message_label->setText(tr("custom / unlock"));
  else if (click_button == cancel_button)
    message_label->setText(tr("custom / no cancel button"));
}