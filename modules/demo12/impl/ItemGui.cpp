#include "ItemGui.h"

ItemGui::ItemGui(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("ItemGui");

  width = height = 500;
  view = new QGraphicsView;
  view->setMaximumSize(width, height);

  scene = new QGraphicsScene;
  scene->setSceneRect(-width / 2., -height / 2., width, height);
  view->setScene(scene);

  setCentralWidget(view);

  auto menuBar = this->menuBar();
  auto menu = menuBar->addMenu("添加");

  auto action1 = new QAction("添加视图");
  connect(action1, SIGNAL(triggered(bool)), this, SLOT(slot_addEllipse()));
  menu->addAction(action1);
}

ItemGui::~ItemGui() noexcept = default;

void ItemGui::slot_addEllipse() {
  auto item = new QGraphicsEllipseItem;
  item->setRect(QRectF(0, 0, 60, 40));
  srand(time(nullptr));
  // 设置边框
  QPen pen;
  pen.setWidth(2);
  pen.setColor(QColor(rand() % 255, rand() % 255, rand() % 255));
  item->setPen(pen);
  // 填充
  item->setBrush(QBrush(QColor(rand() % 255, rand() % 255, rand() % 255)));
  // 设置可移动
  item->setFlag(QGraphicsItem::ItemIsMovable);
  // 大小随机
  item->setScale((rand() % 10 + 1) / 5.0);
  // 位置随机
  item->setPos(rand() % width - width / 2., rand() % height - height / 2.);
  scene->addItem(item);
}

void ItemGui::slot_addText() {}

void ItemGui::slot_addPixmap() {}

void ItemGui::slot_addFlash() {}

void ItemGui::slot_addAnimation() {}