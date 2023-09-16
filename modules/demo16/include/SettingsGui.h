#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <QColorDialog>
#include <QLabel>
#include <QPushButton>
#include <QSettings> // 注册表类
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class SettingsGui : public QWidget {
  Q_OBJECT
public:
  explicit SettingsGui(QWidget *parent = nullptr);
  ~SettingsGui() noexcept override;

  void writeSettings();
  void readSettings();
  void closeEvent(QCloseEvent *event) override;

public slots:
  void slot_changeColor();

private:
  QLabel *label;
  QTextEdit *textEdit;
};

#endif // KEYEVENT_H
