#include "KeyEventGui.h"

KeyEventGui::KeyEventGui(QWidget *parent) : QWidget(parent) {
  setWindowTitle("Key Event GUI");
  setFixedSize(1024, 512);
  width = size().width();
  height = size().height();

  pixmap = new QPixmap(width, height);
  pixmap->fill(Qt::white);
  painter = new QPainter(pixmap);
  image.load(":/images/1.png");

  step = 32;
  x = y = 0;
  drawPixmap();

  qDebug() << "构造函数" << Qt::endl;
}

KeyEventGui::~KeyEventGui() noexcept = default;

void KeyEventGui::paintEvent(QPaintEvent *event) {
  qDebug() << "keyEvent" << Qt::endl;
  // 给整个页面绘制pix
  QPainter painter1(this);
  painter1.drawPixmap(QPoint(0, 0), *pixmap);
}

void KeyEventGui::drawPixmap() {
  qDebug() << "drawPixmap" << Qt::endl;
  pixmap->fill(Qt::white);
  QPen pen(Qt::DotLine);
  painter->setPen(pen);
  for (int i = step; i < width; i += step) {
    painter->drawLine(QPoint(i, 0), QPoint(i, height));
    painter->drawLine(QPoint(0, i), QPoint(width, i));
  }
  painter->drawImage(QPoint(x, y), image);
}

void KeyEventGui::keyPressEvent(QKeyEvent *event) {
  qDebug() << "keyPressEvent" << Qt::endl;
  if (event->modifiers() == Qt::ControlModifier) { // 如果同时按下Ctrl键
    if (event->key() == Qt::Key_Left) // 如果是左键，向左移1
      x = (x - 1 < 0) ? x : x - 1;
    else if (event->key() == Qt::Key_Right) // 如果是右键，向右移1
      x = (x + 1 + image.width() > width) ? x : x + 1;
    else if (event->key() == Qt::Key_Up) // 如果是向上键，向上移1
      y = (y - 1 < 0) ? y : y - 1;
    else if (event->key() == Qt::Key_Down) // 如果是向下键，向下移1
      y = (y + 1 + image.height() > height) ? y : y + 1;
  } else { // 直接按，未组合Ctrl
    // x = x - x % step;    //x坐标留整，32的整数倍
    // y = y - y % step;    //y坐标留整

    if (event->key() == Qt::Key_Left) // 如果是左键,向左移32
      x = (x - step < 0) ? x : x - step;
    else if (event->key() == Qt::Key_Right) // 如果是右键，向右移32
      x = (x + step + image.width() > width) ? x : x + step;
    else if (event->key() == Qt::Key_Up) // 如果是向上键，向上移32
      y = (y - step < 0) ? y : y - step;
    else if (event->key() == Qt::Key_Down) // 如果是向下键，向下移动32
      y = (y + step + image.height() > height) ? y : y + step;
    else if (event->key() == Qt::Key_Home) { // 如果是HOME键,则到开头
      x = y = 0;
    } else if (event->key() == Qt::Key_End) { // 如果是end键,则到结尾
      x = width - image.width();
      y = height - image.height();
    }
  }
  drawPixmap();   // 重新画背景线和前景图片
  this->update(); // 界面更新
}

void KeyEventGui::keyReleaseEvent(QKeyEvent *event) {
  qDebug() << "keyReleaseEvent" << Qt::endl;
  auto key = event->key();
  qDebug() << "releaseKey Num : " << key << Qt::endl;
  if (key >= 32 && key <= 126)
    qDebug() << "releaseKey Char : " << (char)key << Qt::endl;
}