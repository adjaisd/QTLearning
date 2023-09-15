#ifndef MAPGUI_H
#define MAPGUI_H

#include <QDebug>
#include <QFile>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QSlider>
#include <QTextStream>
#include <QVBoxLayout>
#include <QWidget>

class MapGui : public QGraphicsView {
  Q_OBJECT
public:
  explicit MapGui(QWidget * = nullptr);
  ~MapGui() noexcept override;

  // 加载图片
  void loadMap();

  // 画背景函数
  void drawBackground(QPainter *painter, const QRectF &rect) override;

  // 鼠标点击事件，改变label位置
  void mousePressEvent(QMouseEvent *event) override;

  // 坐标转换为经纬度
  QPointF ScenePosToMap(const QPointF &p);

private:
  QPixmap pixmap; // 保存图片数据
  int oldZoom{};  // 保存焦距
  QLabel *view_label{};
  QLabel *scene_label{};
  QLabel *map_label{};
  float x1{}, y1{}; // 左上的经纬度
  float x2{}, y2{}; // 右下经纬度
public slots:
  void slot_scale(int zoom); // 缩放
};

#endif // MAPGUI_H
