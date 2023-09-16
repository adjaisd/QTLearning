#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QDebug>
#include <QImage>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QWidget>

class KeyEventGui : public QWidget {
  Q_OBJECT
public:
  explicit KeyEventGui(QWidget *parent = nullptr);
  ~KeyEventGui() noexcept override;

  void drawPixmap();
  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

private:
  QPainter *painter;
  QPixmap *pixmap;
  QImage image;
  int x, y;
  int width, height;
  int step;
};

#endif // KEYEVENT_H
