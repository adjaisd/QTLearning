#ifndef QQ_H
#define QQ_H

#include <QGroupBox>
#include <QToolBox>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

class QQ : public QToolBox {
  Q_OBJECT
public:
  explicit QQ(QWidget *parent = nullptr);
  ~QQ() noexcept override;
  static QToolButton *add_button(const QString &name, const QString &iconPath);
public slots:
private:
};

#endif // QQ_H
