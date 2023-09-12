#include <QInputDialog>
#include "Input.h"

Input::Input(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Input示例");

    //提示label
    auto *label1 = new QLabel("姓名");
    auto *label2 = new QLabel("性别");
    auto *label3 = new QLabel("年龄");
    auto *label4 = new QLabel("身高");

    name_label = new QLabel;
    sex_label = new QLabel;
    age_label = new QLabel;
    height_label = new QLabel;

    //面板label
    //设置QFrame对象样式为Panel、Sunken
    name_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    sex_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    age_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    height_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);

    //按钮
    auto *name_button = new QPushButton;
    auto *sex_button = new QPushButton;
    auto *age_button = new QPushButton;
    auto *height_button = new QPushButton;

    name_button->setIcon(QIcon(":/images/btn.png"));    // :代表根目录
    sex_button->setIcon(QIcon(":/images/btn.png"));
    age_button->setIcon(QIcon(":/images/btn.png"));
    height_button->setIcon(QIcon(":/images/btn.png"));

    //布局
    auto *gridLayout = new QGridLayout(this);
    //auto *gridLayout = new QGridLayout;
    //setLayout(gridLayout);

    //设置第1列最小宽度100px
    gridLayout->setColumnMinimumWidth(1, 100);

    gridLayout->addWidget(label1, 0, 0);
    gridLayout->addWidget(label2, 1, 0);
    gridLayout->addWidget(label3, 2, 0);
    gridLayout->addWidget(label4, 3, 0);

    gridLayout->addWidget(name_label, 0, 1);
    gridLayout->addWidget(sex_label, 1, 1);
    gridLayout->addWidget(age_label, 2, 1);
    gridLayout->addWidget(height_label, 3, 1);

    gridLayout->addWidget(name_button, 0, 2);
    gridLayout->addWidget(sex_button, 1, 2);
    gridLayout->addWidget(age_button, 2, 2);
    gridLayout->addWidget(height_button, 3, 2);

    //connect
    connect(name_button, SIGNAL(clicked(bool)), this, SLOT(slot_getName()));
    connect(sex_button, SIGNAL(clicked(bool)), this, SLOT(slot_getSex()));
    connect(age_button, SIGNAL(clicked(bool)), this, SLOT(slot_getAge()));
    connect(height_button, SIGNAL(clicked(bool)), this, SLOT(slot_getHeight()));
}

Input::~Input() noexcept = default;

void Input::slot_getName() {
    bool ok;
    //QLineEdit::Normal为文本输入框
    auto name =
            QInputDialog::getText(this, "文本输入框", "姓名", QLineEdit::Normal, "张三", &ok);
    if (ok && !name.trimmed().isEmpty()) name_label->setText(name);
}

void Input::slot_getSex() {
    bool ok;
    QStringList sexlist;
    sexlist.push_back("男");
    sexlist.push_back("女");
    auto sex = QInputDialog::getItem(this, "选项输入框", "性别", sexlist, 0, false, &ok);
    if (ok) sex_label->setText(sex);
}

void Input::slot_getAge() {
    bool ok;
    auto age = QInputDialog::getInt(this, "整型输入框", "年 龄", 18, 1, 100, 1, &ok);
    if (ok) age_label->setText(QString::number(age));
}

void Input::slot_getHeight() {
    bool ok;
    //decimals：保留几位小数
    double height = QInputDialog::getDouble(this, "浮点型输入框", "身 高", 160, 160, 200, 2, &ok);
    if (ok) height_label->setText(QString::number(height));
}