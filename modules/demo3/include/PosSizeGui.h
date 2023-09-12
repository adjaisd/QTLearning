#ifndef POSSIZEGUI_H
#define POSSIZEGUI_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>

class PosSizeGui : public QDialog {
public:
    explicit PosSizeGui(QWidget *parent = 0);

    ~PosSizeGui();

    QLabel *x_label{};
    QLabel *y_label{};
    QLabel *frameGeometry_label{};
    QLabel *geometry_label{};
    QLabel *rect_label{};
    QLabel *pos_label{};
    QLabel *frameSize_label{};
    QLabel *size_label{};
    QLabel *wh_label{};

    void update_label();

public slots:
    //重写事件处理函数，当相应的事件发生时，自动调用
    void moveEvent(QMoveEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    void showEvent(QShowEvent *) override;
    void closeEvent(QCloseEvent *) override;
};


#endif //POSSIZEGUI_H
