#include "LcdNumber.h"

LcdNumber::LcdNumber(QWidget *parent) : QLCDNumber(parent) {
  setWindowTitle("LcdNumber示例");

  resize(120, 60);
  // 显示字符的个数，hh:mm 的个数是5
  this->setDigitCount(8);

  // 设置颜色
  QPalette palette = this->palette();
  // QFrame 背景色：window  文本颜色：WindowText
  // Button 背景色：button  文本颜色：ButtonText
  // edit  背景色：base    文本颜色：text
  palette.setColor(QPalette::Window, Qt::blue);
  palette.setColor(QPalette::WindowText, Qt::red);
  setPalette(palette);

  // 设置透明度
  setWindowOpacity(0.6);

  isShow = true;

  // 定时器
  auto *timer = new QTimer;
  connect(timer, SIGNAL(timeout()), this, SLOT(slot_showTime()));
  // 每隔500毫秒发送timeout信号
  timer->start(500);
}

LcdNumber::~LcdNumber() noexcept = default;

void LcdNumber::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton)
    posMinus = event->globalPos() - frameGeometry().topLeft();
  event->accept();
}

void LcdNumber::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::LeftButton) {
    move(event->globalPos() - posMinus);
    event->accept();
  }
}

void LcdNumber::slot_showTime() {
  QTime tm = QTime::currentTime();
  QString tmStr = tm.toString("hh:mm:ss");
  if (isShow)
    tmStr[2] = ':';
  else
    tmStr[2] = ' ';
  display(tmStr);
  isShow = !isShow;
}