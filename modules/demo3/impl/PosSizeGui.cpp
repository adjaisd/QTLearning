#include "PosSizeGui.h"

PosSizeGui::PosSizeGui(QWidget *parent) : QDialog(parent) {
    setWindowTitle("窗口位置大小示例");

    auto *label1 = new QLabel("x()");
    auto *label2 = new QLabel("y()");
    auto *label3 = new QLabel("frameGeometry()");
    auto *label4 = new QLabel("geometry()");
    auto *label5 = new QLabel("rect()");
    auto *label6 = new QLabel("pos)");
    auto *label7 = new QLabel("frameSize()");
    auto *label8 = new QLabel("size()");
    auto *label9 = new QLabel("wh()");

    x_label = new QLabel;
    y_label = new QLabel;
    frameGeometry_label = new QLabel;
    geometry_label = new QLabel;
    rect_label = new QLabel;
    pos_label = new QLabel;
    frameSize_label = new QLabel;
    size_label = new QLabel;
    wh_label = new QLabel;

    auto *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(label1, 0, 0);
    gridLayout->addWidget(label2, 1, 0);
    gridLayout->addWidget(label3, 2, 0);
    gridLayout->addWidget(label4, 3, 0);
    gridLayout->addWidget(label5, 4, 0);
    gridLayout->addWidget(label6, 5, 0);
    gridLayout->addWidget(label7, 6, 0);
    gridLayout->addWidget(label8, 7, 0);
    gridLayout->addWidget(label9, 8, 0);

    gridLayout->addWidget(x_label, 0, 1);
    gridLayout->addWidget(y_label, 1, 1);
    gridLayout->addWidget(frameGeometry_label, 2, 1);
    gridLayout->addWidget(geometry_label, 3, 1);
    gridLayout->addWidget(rect_label, 4, 1);
    gridLayout->addWidget(pos_label, 5, 1);
    gridLayout->addWidget(frameSize_label, 6, 1);
    gridLayout->addWidget(size_label, 7, 1);
    gridLayout->addWidget(wh_label, 8, 1);
}

PosSizeGui::~PosSizeGui() = default;

void PosSizeGui::update_label() {
    QString xstr = QString::number(this->x());
    x_label->setText(xstr);

    QString ystr = QString::number(this->y());
    y_label->setText(ystr);

    QRect frameGeometryRect = this->frameGeometry();
    QString frameGeometryRectStr =
            QString::number(frameGeometryRect.x())
            + "," + QString::number(frameGeometryRect.y())
            + "," + QString::number(frameGeometryRect.width())
            + "," + QString::number(frameGeometryRect.height());
    frameGeometry_label->setText(frameGeometryRectStr);

    QRect geometryRect = this->geometry();
    QString geometryRectStr =
            QString::number(geometryRect.x())
            + "," + QString::number(geometryRect.y())
            + "," + QString::number(geometryRect.width())
            + "," + QString::number(geometryRect.height());
    geometry_label->setText(geometryRectStr);

    QRect rect1 = this->rect();
    QString rectStr =
            QString::number(rect1.x())
            + "," + QString::number(rect1.y())
            + "," + QString::number(rect1.width())
            + "," + QString::number(rect1.height());
    rect_label->setText(rectStr);

    QPoint pos = this->pos();
    QString posStr = QString::number(pos.x()) + "," + QString::number(pos.y());
    pos_label->setText(posStr);

    QSize frameSize1 = this->frameSize();
    QString frameSize1Str = QString::number(frameSize1.width())
                            + "," + QString::number(frameSize1.height());
    frameSize_label->setText(frameSize1Str);

    QSize size1 = this->size();
    QString size1Str =
            QString::number(size1.width())
            + "," + QString::number(size1.height());
    size_label->setText(size1Str);

    QString whStr = QString::number(this->width()) + "," + QString::number(this->height());
    wh_label->setText(whStr);
}

void PosSizeGui::moveEvent(QMoveEvent *moveEvent) {
    qDebug() << "moveEvent" << Qt::endl;
    update_label();
}

void PosSizeGui::resizeEvent(QResizeEvent *resizeEvent) {
    qDebug() << "resizeEvent" << Qt::endl;
    update_label();
}

void PosSizeGui::keyPressEvent(QKeyEvent *keyEvent) {
    qDebug() << "keyPressEvent" << Qt::endl;
    update_label();
}

void PosSizeGui::showEvent(QShowEvent *showEvent) {
    qDebug() << "showEvent" << Qt::endl;
    update_label();
}

void PosSizeGui::closeEvent(QCloseEvent *closeEvent) {
    qDebug() << "closeEvent" << Qt::endl;
    update_label();
}