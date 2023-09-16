#include "MouseEventGui.h"

MouseEventGui::MouseEventGui(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("MouseEventGUI");
  resize(400, 300);

  eventLabel = new QLabel("事件");
  eventLabel->setFixedWidth(150);

  posLabel = new QLabel("位置");
  posLabel->setFixedWidth(150);

  auto statusBar = this->statusBar();
  statusBar->addWidget(eventLabel);
  statusBar->addWidget(posLabel);

  this->setMouseTracking(true); // 鼠标追踪
}

MouseEventGui::~MouseEventGui() noexcept = default;

void MouseEventGui::mousePressEvent(QMouseEvent *event) {
  QString eventStr = "";
  if (event->button() == Qt::LeftButton)
    eventStr = "鼠标左键";
  else if (event->button() == Qt::RightButton)
    eventStr = "鼠标右键";
  else if (event->button() == Qt::MiddleButton)
    eventStr = "鼠标中键";

  eventLabel->setText(eventStr);

  auto posStr = QString::number(event->pos().x()) + "," +
                QString::number(event->pos().y());
  posLabel->setText(posStr);
}

void MouseEventGui::mouseReleaseEvent(QMouseEvent *event) {
  QString eventStr = "";
  if (event->button() == Qt::LeftButton)
    eventStr = "鼠标左键释放";
  else if (event->button() == Qt::RightButton)
    eventStr = "鼠标右键释放";
  else if (event->button() == Qt::MiddleButton)
    eventStr = "鼠标中键释放";

  eventLabel->setText(eventStr);

  auto posStr = QString::number(event->pos().x()) + "," +
                QString::number(event->pos().y());
  posLabel->setText(posStr);
}

void MouseEventGui::mouseDoubleClickEvent(QMouseEvent *event) {
  QString eventStr = "";
  if (event->button() == Qt::LeftButton)
    eventStr = "鼠标左键双击";
  else if (event->button() == Qt::RightButton)
    eventStr = "鼠标右键双击";
  else if (event->button() == Qt::MiddleButton)
    eventStr = "鼠标中键双击";

  eventLabel->setText(eventStr);

  auto posStr = QString::number(event->pos().x()) + "," +
                QString::number(event->pos().y());
  posLabel->setText(posStr);
}

void MouseEventGui::mouseMoveEvent(QMouseEvent *event) {
  QString eventStr = "";
  if (event->buttons() & Qt::LeftButton)
    eventStr = "鼠标左键拖动";
  else if (event->button() & Qt::RightButton)
    eventStr = "鼠标右键拖动";
  else if (event->button() & Qt::MiddleButton)
    eventStr = "鼠标中键拖动";

  eventLabel->setText(eventStr);

  auto posStr = QString::number(event->pos().x()) + "," +
                QString::number(event->pos().y());
  posLabel->setText(posStr);
}