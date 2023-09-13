#include "TableGUI.h"

TableGUI::TableGUI(QWidget *parent) : QTableWidget(parent) {
  setWindowTitle("table示例");

  resize(650, 220);
  setRowCount(5);
  setColumnCount(5);

  // 表头
  auto head_item1 = new QTableWidgetItem("性别");
  auto head_item2 = new QTableWidgetItem("姓名");
  auto head_item3 = new QTableWidgetItem("生日");
  auto head_item4 = new QTableWidgetItem("工作");
  auto head_item5 = new QTableWidgetItem("工资");

  setItem(0, 0, head_item1);
  setItem(0, 1, head_item2);
  setItem(0, 2, head_item3);
  setItem(0, 3, head_item4);
  setItem(0, 4, head_item5);

  // 添加行数据
  add_row(1, MAN, "张三", QDate(2000,1,1), 1,5000);
  add_row(2,WOMAN,"李四",QDate(2000,1,1),2,5000);
  add_row(3,MAN,"王五",QDate(2000,1,1),3,5000);
  add_row(4,MAN,"赵六",QDate(2000,1,1),0,5000);
}

TableGUI::~TableGUI() noexcept = default;

void TableGUI::add_row(int row, enum SEX_ENUM sex, const QString &name,
                       const QDate &date, int id, int sales) {
  if (row < 0 || name.trimmed().isEmpty() || id < 0)
    return;
  auto sex_label = new QLabel;
  if (sex == MAN)
    sex_label->setPixmap(QPixmap(":/images/Male.png"));
  else
    sex_label->setPixmap(QPixmap(":/images/Female.png"));
  sex_label->setAlignment(Qt::AlignCenter);

  auto name_tableWidgetItem = new QTableWidgetItem(name);
  name_tableWidgetItem->setTextAlignment(Qt::AlignCenter);

  auto date_edit = new QDateTimeEdit;
  date_edit->setDate(date);
  date_edit->setDisplayFormat("yyyy-MM-dd");
  date_edit->setCalendarPopup(true);

  auto work_comboBox = new QComboBox;
  work_comboBox->addItem("工 人");
  work_comboBox->addItem("农 民");
  work_comboBox->addItem("学 生");
  work_comboBox->addItem("军 人");
  work_comboBox->setCurrentIndex(id);

  auto *sale_spinBox = new QSpinBox;
  sale_spinBox->setRange(3000, 10000);
  sale_spinBox->setSingleStep(100);
  sale_spinBox->setAlignment(Qt::AlignCenter);

  setCellWidget(row, 0, sex_label);
  setItem(row, 1, name_tableWidgetItem);
  setCellWidget(row, 2, date_edit);
  setCellWidget(row, 3, work_comboBox);
  setCellWidget(row, 4, sale_spinBox);
}