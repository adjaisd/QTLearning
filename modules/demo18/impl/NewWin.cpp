#include "NewWin.h"

NewWin::NewWin(QWidget *parent) : QWidget(parent) {
  setWindowTitle("NewWin");

  textEdit = new QTextEdit;
  auto button = new QPushButton("发送");
  auto vbLayout = new QVBoxLayout(this);
  vbLayout->addWidget(button);
  vbLayout->addWidget(textEdit);

  connect(button, SIGNAL(clicked(bool)), this, SLOT(slot_sendOk()));
}

NewWin::~NewWin() noexcept = default;

void NewWin::slot_sendOk() { emit sendData(textEdit->toPlainText()); }