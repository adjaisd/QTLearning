#ifndef TABLEGUI_H
#define TABLEGUI_H

#include <QComboBox>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QLabel>
#include <QSpinBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QWidget>

class TableGUI : public QTableWidget {
  Q_OBJECT
public:
  explicit TableGUI(QWidget * = nullptr);
  ~TableGUI() noexcept override;

  enum SEX_ENUM { MAN, WOMAN };

  void add_row(int, enum SEX_ENUM, const QString &, const QDate &, int, int);
public slots:
private:
};

#endif // TABLEGUI_H
