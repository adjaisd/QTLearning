#include "SignalGUI.h"
#include "NewWin.h"

SignalGUI::SignalGUI(QWidget *parent) : QWidget(parent) {
  setWindowTitle("SignalGUI");

  resize(500, 100);
  label = new QLabel(this);
  label->resize(size());
  label->setText("no text");
  label->setAlignment(Qt::AlignCenter);

  auto newWin = new NewWin;
  newWin->show();
  connect(newWin, SIGNAL(sendData(QString)), this,
          SLOT(slot_showText(QString)));
}

SignalGUI::~SignalGUI() noexcept = default;

void SignalGUI::slot_showText(const QString &text) { label->setText(text); }