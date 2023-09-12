#include "dialogTest.h"


DialogTest::DialogTest(QWidget *parent) :
        QWidget(parent) {
    setWindowTitle("测试DialogTest.exe");

    // 输入框
    file_edit = new QLineEdit;
    font_edit = new QLineEdit("Hello, world.");
    color_frame = new QFrame;
    color_frame->setFrameShape(QFrame::Box);
    color_frame->setAutoFillBackground(true);

    // 按钮
    auto *file_button = new QPushButton("文件");
    auto *font_button = new QPushButton("字体");
    auto *color_button = new QPushButton("颜色");

    connect(file_button, SIGNAL(clicked(bool)), this, SLOT(slot_getFileName()));
    connect(font_button, SIGNAL(clicked(bool)), this, SLOT(slot_getFont()));
    connect(color_button, SIGNAL(clicked(bool)), this, SLOT(slot_getColor()));

    //网格布局
    auto *gridLayout = new QGridLayout(this);

    //第一行
    gridLayout->addWidget(file_button, 0, 0);
    gridLayout->addWidget(file_edit, 0, 1);
    //第二行
    gridLayout->addWidget(font_button, 1, 0);
    gridLayout->addWidget(font_edit, 1, 1);
    //第三行
    gridLayout->addWidget(color_button, 2, 0);
    gridLayout->addWidget(color_frame, 2, 1);
}

void DialogTest::slot_getFileName() {
    QString pathName = QFileDialog::getOpenFileName(this, "文件对话框", "../../","C++ head(*.h);;source(*.cpp);;all file(*"
                                                                          ".*)");
    qDebug() << pathName << Qt::endl;
    // trimmed: 去掉空格
    if (pathName.trimmed().isDetached()) return;
    file_edit->setText(pathName);
}

void DialogTest::slot_getFont() {
    bool ok;
    QFont font = QFontDialog::getFont(&ok);
    if(ok) font_edit->setFont(font);
}

void DialogTest::slot_getColor() {
    QColor color = QColorDialog::getColor(Qt::red, this);
    if(color.isValid()) {
        // 设置颜色
        color_frame->setPalette(QPalette(color));
    }
}

DialogTest::~DialogTest() = default;
