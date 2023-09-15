#ifndef POSITEM_H
#define POSITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QWidget>
#include <QDebug>

class PosItem : public QObject, public QGraphicsItem {
  Q_OBJECT
public:
  explicit PosItem(QGraphicsItem *parent = nullptr);
  ~PosItem() noexcept override;
  QRectF boundingRect() const override;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
             QWidget *widget = nullptr) override;

private:
  QPixmap pixmap;
};

#endif // POSITEM_H