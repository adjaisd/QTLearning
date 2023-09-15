#ifndef FLASHITEM_H
#define FLASHITEM_H

#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QWidget>
#include <QDebug>

class FlashItem : public QObject, public QGraphicsItem {
  Q_OBJECT
public:
  explicit FlashItem(QGraphicsItem *graphicsItem = nullptr);
  ~FlashItem() noexcept override;
  void timerEvent(QTimerEvent *event) override;
  QRectF boundingRect() const override;  // 返回组件自身位置和大小
  void paint(QPainter*painter, const QStyleOptionGraphicsItem *option,
             QWidget*widget) override;
private:
  int timerId;    // 定时器id
  bool showColor; // 控制显示颜色
};

#endif // FLASHITEM_H