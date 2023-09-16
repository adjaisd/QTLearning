#ifndef SIGNALGUI_H
#define SIGNALGUI_H

#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class SignalGUI : public QWidget {
  Q_OBJECT
public:
  explicit SignalGUI(QWidget *parent = nullptr);
  ~SignalGUI() noexcept override;
public slots:
  void slot_showText(const QString &text);

private:
  QLabel *label;
};

#endif // SIGNALGUI_H
