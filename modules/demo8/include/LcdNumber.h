#ifndef LCDNUMBER_H
#define LCDNUMBER_H

#include <QLCDNumber>
#include <QMouseEvent>
#include <QPalette>
#include <QTime>
#include <QTimer>
#include <QWidget>

class LcdNumber : public QLCDNumber {
  Q_OBJECT
public:
  explicit LcdNumber(QWidget * = nullptr);
  ~LcdNumber() noexcept override;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

public slots:
  void slot_showTime();

private:
  bool isShow;
  QPoint posMinus;
};

#endif // LCDNUMBER_H
