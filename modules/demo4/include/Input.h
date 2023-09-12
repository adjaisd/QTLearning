#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QGridLayout>

class Input : public QDialog {
Q_OBJECT

public:
    explicit Input(QWidget *parent = nullptr);

    ~Input() noexcept override;

public slots:

    void slot_getName();

    void slot_getSex();

    void slot_getAge();

    void slot_getHeight();

private:
    QLabel *name_label;
    QLabel *sex_label;
    QLabel *age_label;
    QLabel *height_label;
};


#endif //INPUT_H
