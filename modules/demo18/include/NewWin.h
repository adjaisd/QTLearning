#ifndef NewWin_H
#define NewWin_H

#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

class NewWin : public QWidget {
  Q_OBJECT
public:
  explicit NewWin(QWidget *parent = nullptr);
  ~NewWin() noexcept override;

signals:
  void sendData(QString text);

public slots:
  void slot_sendOk();

private:
  QTextEdit *textEdit;
};

#endif // NewWin_H