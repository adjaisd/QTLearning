#include "ItemGui.h"
#include "FlashItem.h"
#include "PosItem.h"

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

  auto action1 = new QAction("添加椭圆");
  connect(action1, SIGNAL(triggered(bool)), this, SLOT(slot_addEllipse()));
  menu->addAction(action1);

  auto action2 = new QAction("添加文本");
  connect(action2, SIGNAL(triggered(bool)), this, SLOT(slot_addText()));
  menu->addAction(action2);

  auto action3 = new QAction("添加图片");
  connect(action3, SIGNAL(triggered(bool)), this, SLOT(slot_addPixmap()));
  menu->addAction(action3);

  auto action4 = new QAction("添加闪烁");
  connect(action4, SIGNAL(triggered(bool)), this, SLOT(slot_addFlash()));
  menu->addAction(action4);

  auto action5 = new QAction("添加动画");
  connect(action5, SIGNAL(triggered(bool)), this, SLOT(slot_addAnimation()));
  menu->addAction(action5);

  auto action6 = new QAction("清空");
  connect(action6, SIGNAL(triggered(bool)), this, SLOT(slot_clear()));
  menu->addAction(action6);
}

ItemGui::~ItemGui() noexcept {
  qDebug() << "ItemGui::~ItemGUI()" << Qt::endl;
  slot_clear();
}

void ItemGui::slot_clear() {
  qDebug() << "ItemGui::slot_clear()" << Qt::endl;
  auto itemList = scene->items();
  int c = 0;
  while (!itemList.isEmpty()) {
    qDebug() << "deleting item : " << ++c << Qt::endl;
    scene->removeItem(itemList.first());
    itemList.removeFirst();
  }
  qDebug() << "left: " << scene->items().size() << Qt::endl;
}

void ItemGui::slot_addEllipse() {
  srand(time(nullptr));
  auto item = new QGraphicsEllipseItem;
  item->setRect(QRectF(0, 0, 60, 40));
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

void ItemGui::slot_addText() {
  srand(time(nullptr));
  auto item = new QGraphicsTextItem("TextItem");
  item->setFlag(QGraphicsItem::ItemIsMovable);
  item->setScale((rand() % 10 + 1) / 5.0);
  item->setPos(rand() % width - width / 2., rand() % height - height / 2.);
  item->setFont(QFont("宋体"));
  item->setDefaultTextColor(QColor(rand() % 255, rand() % 255, rand() % 255));
  scene->addItem(item);
}

void ItemGui::slot_addPixmap() {
  srand(time(nullptr));
  auto item = new QGraphicsPixmapItem;
  item->setPixmap(QPixmap(":/images/butterfly.png"));
  item->setFlag(QGraphicsItem::ItemIsMovable);
  item->setScale((rand() % 10 + 1) / 5.0);
  item->setPos(rand() % width - width / 2., rand() % height - height / 2.);
  scene->addItem(item);
}

void ItemGui::slot_addFlash() {
  srand(time(nullptr));
  auto item = new FlashItem;
  item->setScale((rand() % 10 + 1) / 5.0);
  item->setPos(rand() % width - width / 2., rand() % height - height / 2.);
  scene->addItem(item);
}

void ItemGui::slot_addAnimation() {
  srand(time(nullptr));
  auto item = new PosItem;
  auto animation = new QGraphicsItemAnimation;
  animation->setItem(item);
  auto timeLine = new QTimeLine(5000);
  timeLine->setEasingCurve(QEasingCurve::SineCurve); // 退出效果
  timeLine->setLoopCount(0);                         // 永久循环
  animation->setTimeLine(timeLine);
  timeLine->start();

  int y = (rand() % 400) - 200;
  for (int i = 0; i < 400; ++i)
    animation->setPosAt(i / 400., QPointF(i - 200, y));
  scene->addItem(item);
}