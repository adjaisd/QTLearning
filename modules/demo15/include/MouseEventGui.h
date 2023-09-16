#ifndef MOUSEEVENTGUI_H
#define MOUSEEVENTGUI_H

#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>
#include <QStatusBar>

class MouseEventGui : public QMainWindow {
  Q_OBJECT
public:
  explicit MouseEventGui(QWidget *parent = nullptr);
  ~MouseEventGui() noexcept override;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

private:
  QLabel *eventLabel;
  QLabel *posLabel;
};

#endif // MOUSEEVENTGUI_H
