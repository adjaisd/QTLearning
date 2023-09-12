#ifndef MESSAGEGUI_H
#define MESSAGEGUI_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout> // 垂直布局

class MessageGUI : public QDialog {
  Q_OBJECT
public:
  explicit MessageGUI(QWidget *parent = nullptr);
  ~MessageGUI() noexcept override;
public slots:
  void slot_question();
  void slot_information();
  void slot_warning();
  void slot_critical();
  void slot_about();
  void slot_aboutQt();
  void slot_custom();

private:
  QLabel *message_label{};
};

#endif // MESSAGEGUI_H
