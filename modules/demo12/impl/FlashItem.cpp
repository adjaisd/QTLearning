#include "FlashItem.h"

FlashItem::FlashItem(QGraphicsItem *graphicsItem)
    : QGraphicsItem(graphicsItem) {
  showColor = true;
  setFlag(QGraphicsItem::ItemIsMovable);
  timerId = startTimer(100);
}

FlashItem::~FlashItem() noexcept {
  killTimer(timerId);
  qDebug() << "FlashItem::FlashItem()" << Qt::endl;
}

QRectF FlashItem::boundingRect() const {
  qDebug() << "FlashItem::boundingRect()" << Qt::endl;
  return {0, 0, 40, 40};
}

void FlashItem::timerEvent(QTimerEvent *event) {
  qDebug() << "FlashItem::timeEvent()" << Qt::endl;
  showColor = !showColor;
  update();
}

void FlashItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget) {
  qDebug() << "void FlashItem::paint" << Qt::endl;
  painter->setBrush(showColor ? Qt::red : Qt::yellow);
  painter->drawEllipse(boundingRect());
}