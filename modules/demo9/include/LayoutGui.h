#ifndef LAYOUTGUI_H
#define LAYOUTGUI_H

#include <QButtonGroup>
#include <QCheckBox>
#include <QComboBox>
#include <QDate>
#include <QDateEdit>
#include <QFileDialog>
#include <QGridLayout>
#include <QHBoxLayout> //水平布局
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class LayoutGui : public QWidget {
  Q_OBJECT
public:
  explicit LayoutGui(QWidget * = nullptr);
  ~LayoutGui() noexcept override;

public slots:
  void slot_changeHead();
private:
  QLabel *avatar_label;
};

#endif // LAYOUTGUI_H
