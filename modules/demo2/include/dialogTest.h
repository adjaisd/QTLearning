#ifndef DIALOGTEST_H
#define DIALOGTEST_H

#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QFontDialog>
#include <QColorDialog>
#include <QWidget>

class DialogTest: public QWidget {
    Q_OBJECT
public:
    explicit DialogTest(QWidget *parent= nullptr);

    ~DialogTest() override;

public:
    QLineEdit *file_edit;
    QLineEdit *font_edit;
    QFrame *color_frame;

public slots:
    void slot_getFileName();
    void slot_getFont();
    void slot_getColor();
};

#endif //DIALOGTEST_H
