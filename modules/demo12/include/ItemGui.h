#ifndef ITEMGUI_H
#define ITEMGUI_H

#include <QAction>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsItemAnimation>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTimeLine>
#include <ctime>

class ItemGui : public QMainWindow {
  Q_OBJECT
public:
  explicit ItemGui(QWidget *parent = nullptr);
  ~ItemGui() noexcept override;

public slots:
  void slot_addEllipse();
  void slot_addText();
  void slot_addPixmap();
  void slot_addFlash();
  void slot_addAnimation();

private:
  QGraphicsView *view;
  QGraphicsScene *scene;
  int width;
  int height;
};

#endif // ITEMGUI_H
