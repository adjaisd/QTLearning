#include "MapGui.h"

MapGui::MapGui(QWidget *parent) : QGraphicsView(parent) {
  setWindowTitle("MapGui示例");
  oldZoom = 50;

  // 1.加载图片，货的宽高
  loadMap();
  int width = pixmap.width();
  int height = pixmap.height();
  setMinimumSize(width, height); // 设置view大小

  // 2.利用图片的宽高设置场景的形状和view的形状，设置缓冲模式
  auto scene = new QGraphicsScene;
  scene->setSceneRect(-width / 2., -height / 2., width, height);
  setScene(scene);

  // 创建滑块及label并加入到布局
  auto max_label = new QLabel;
  max_label->setPixmap(QPixmap(":/images/zoomin.png"));
  auto min_label = new QLabel;
  min_label->setPixmap(QPixmap(":/images/zoomout.png"));

  auto slider = new QSlider;
  slider->setOrientation(Qt::Vertical);
  slider->setRange(1, 100);
  slider->setValue(oldZoom);
  slider->setTickInterval(10);
  connect(slider, SIGNAL(valueChanged(int)), this, SLOT(slot_scale(int)));

  auto slider_vLayout = new QVBoxLayout;
  slider_vLayout->addWidget(max_label);
  slider_vLayout->addWidget(slider);
  slider_vLayout->addWidget(min_label);

  // 4.创建位置相关的label，加入布局
  auto label1 = new QLabel("view坐标:");
  auto label2 = new QLabel("scene坐标:");
  auto label3 = new QLabel("map坐标:");

  view_label = new QLabel;
  scene_label = new QLabel;
  map_label = new QLabel;

  auto gLayout = new QGridLayout;
  gLayout->addWidget(label1, 0, 0);
  gLayout->addWidget(label2, 1, 0);
  gLayout->addWidget(label3, 2, 0);

  gLayout->addWidget(view_label, 0, 1);
  gLayout->addWidget(scene_label, 1, 1);
  gLayout->addWidget(map_label, 2, 1);

  auto map_vLayout = new QVBoxLayout;
  map_vLayout->addLayout(gLayout);
  map_vLayout->addStretch();

  // 5.加入水平布局
  auto hLayout = new QHBoxLayout(this);
  hLayout->addLayout(slider_vLayout);
  hLayout->addLayout(map_vLayout);
}

MapGui::~MapGui() noexcept = default;

void MapGui::loadMap() {
  auto path = ":/maps.txt";
  QFile file(path);
  QString mapPath = "";
  if (file.open(QIODevice::ReadOnly)) {
    QTextStream stream(&file);
    if (!stream.atEnd()) {
      stream >> mapPath;
      stream >> x1 >> y1;
      stream >> x2 >> y2;
    }
  }
  file.close();
  pixmap.load(mapPath);
  if (pixmap.isNull()) {
    QMessageBox::critical(this, "图片加载失败", "图片不存在或路径错误",
                          QMessageBox::Ok);
    close();
  }
}

void MapGui::drawBackground(QPainter *painter, const QRectF &rect) {
  qDebug() << "void drawBackground(QPainter *painter, const QRectF &rect)"
           << Qt::endl;
  painter->drawPixmap(sceneRect().topLeft(), pixmap);
}

void MapGui::mousePressEvent(QMouseEvent *event) {
  // 1.设置view坐标
  auto view_pos = event->pos();
  auto view_str =
      QString::number(view_pos.x()) + "," + QString::number(view_pos.y());
  view_label->setText(view_str);

  // 2.设置scene坐标
  auto scene_pos = mapToScene(view_pos);
  auto scene_str =
      QString::number(scene_pos.x()) + "," + QString::number(scene_pos.y());
  scene_label->setText(scene_str);

  auto map_pos = ScenePosToMap(view_pos);
  auto map_str =
      QString::number(map_pos.x()) + "," + QString::number(map_pos.y());
  map_label->setText(map_str);
}

QPointF MapGui::ScenePosToMap(const QPointF &p) {
  QPointF latLon;
  auto w = sceneRect().width();
  auto h = sceneRect().height();
  auto lon = y1 - ((h / 2 + p.y()) * abs(y1 - y2) / h);
  auto lat = x1 - ((w / 2 + p.x()) * abs(x1 - x2) / w);
  latLon.setX(lat);
  latLon.setY(lon);
  return latLon;
}

void MapGui::slot_scale(int zoom) {
  qDebug() << "slot_scale(int zoom); zoom = " << zoom << Qt::endl;
  double s;
  if (zoom > oldZoom) {
    s = pow(1.01, zoom - oldZoom);
  } else if (zoom < oldZoom) {
    s = pow(1 / 1.01, oldZoom - zoom);
  }
  this->scale(s, s);
  oldZoom = zoom;
}