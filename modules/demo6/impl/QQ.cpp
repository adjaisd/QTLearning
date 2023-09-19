#include "QQ.h"

QQ ::QQ(QWidget *parent) : QToolBox(parent) {
  setWindowTitle("my qq");
  // 第1组
  auto groupBox1 = new QGroupBox(this);
  auto verticalBoxLayout1 = new QVBoxLayout(groupBox1);
  // groupBox1->setLayout(verticalBoxLayout1);
  verticalBoxLayout1->addWidget(add_button("bb", ":/images/bb.png"));
  verticalBoxLayout1->addWidget(add_button("jj", ":/images/jj.png"));
  verticalBoxLayout1->addWidget(add_button("hh", ":/images/hh.png"));
  verticalBoxLayout1->addWidget(add_button("yy", ":/images/yy.png"));
  verticalBoxLayout1->addWidget(add_button("nn", ":/images/nn.png"));
  //设置布局里的元素居中
  verticalBoxLayout1->setAlignment(Qt::AlignCenter);
  //添加伸缩空间，将布局里的元素填充到顶上，在按钮添加之后
  verticalBoxLayout1->addStretch();
  //将groupBox添加到ToolBox
  this->addItem(groupBox1,"我的好友");

  //2.添加第二组
  auto groupBox2 = new QGroupBox(this);
  auto verticalBoxLayout2 = new QVBoxLayout(groupBox2);
  verticalBoxLayout2->addWidget(add_button("路人",":/images/1.png"));
  verticalBoxLayout2->addWidget(add_button("123",":/images/2.png"));
  verticalBoxLayout2->addWidget(add_button("ABC",":/images/3.png"));
  verticalBoxLayout2->setAlignment(Qt::AlignCenter);
  verticalBoxLayout2->addStretch();
  this->addItem(groupBox2,"陌生人");
  
  //设置ToolBox的width,height
  this->resize(100,600);
}

QQ::~QQ() noexcept = default;

QToolButton *QQ::add_button(const QString &name, const QString &iconPath) {
  if (name.trimmed().isEmpty() || iconPath.trimmed().isEmpty())
    return nullptr;
  auto button = new QToolButton;
  button->setText(name);
  button->setIcon(QPixmap(iconPath));
  button->setIconSize(QPixmap(iconPath).size());
  // 设置鼠标单击工具按钮凸起
  button->setAutoRaise(true);
  // 设置按钮的样式，ToolButtonTextUnderIcon：文本在图标下面
  button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  return button;
}