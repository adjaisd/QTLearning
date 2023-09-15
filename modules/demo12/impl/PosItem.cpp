#include "PosItem.h"

PosItem::PosItem(QGraphicsItem *parent) : QGraphicsItem(parent) {
  pixmap.load(":/images/image.png");
  setFlag(QGraphicsItem::ItemIsMovable);
}

PosItem::~PosItem() noexcept = default;
QRectF PosItem::boundingRect() const {
  return QRectF(0, 0, pixmap.width(), pixmap.height());
}

void PosItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget) {
  painter->drawPixmap(boundingRect().topLeft(), pixmap);
}