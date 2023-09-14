#include "TextGui.h"

TextGui::TextGui(QWidget *parent) : QMainWindow(parent) {
  setWindowTitle("记事本示例");
  setWindowIcon(QIcon(":/images/new.png"));
  resize(400, 400);
  text_edit = new QTextEdit;
  setCentralWidget(text_edit);
  create_action();
  create_menu();
  create_toolBar();
}

TextGui::~TextGui() noexcept = default;

void TextGui::closeEvent(QCloseEvent *e) {
  set_winCount(get_winCount() - 1);
  qDebug() << "slot_close: " << get_winCount() << Qt::endl;
  close();
}

void TextGui::create_action() {
  new_action = new QAction(QIcon(":/images/new.png"), "新建", this);
  new_action->setShortcut(tr("ctrl+n"));
  new_action->setStatusTip("新建");

  connect(new_action, SIGNAL(triggered(bool)), this, SLOT(slot_new()));

  open_action = new QAction(QIcon(":/images/open.png"), "打开", this);
  open_action->setShortcut(tr("ctrl+o"));
  open_action->setStatusTip("打开");
  connect(open_action, SIGNAL(triggered(bool)), this, SLOT(slot_open()));

  save_action = new QAction(QIcon(":/images/save.png"), "保存", this);
  save_action->setShortcut(tr("ctrl+s"));
  save_action->setStatusTip("保存");
  connect(save_action, SIGNAL(triggered(bool)), this, SLOT(slot_save()));

  exit_action = new QAction(QIcon(":/images/exit.png"), "退出", this);
  exit_action->setShortcut(tr("ctrl+e"));
  connect(exit_action, SIGNAL(triggered(bool)), this, SLOT(close()));

  copy_action = new QAction(QIcon(":/images/copy.png"), "复制", this);
  copy_action->setShortcut(tr("ctrl+c"));
  copy_action->setStatusTip("复制");
  connect(copy_action, SIGNAL(triggered(bool)), text_edit, SLOT(copy()));

  paste_action = new QAction(QIcon(":/images/paste.png"), "粘贴", this);
  paste_action->setShortcut(tr("ctrl+v"));
  paste_action->setStatusTip("粘贴");
  connect(paste_action, SIGNAL(triggered(bool)), text_edit, SLOT(paste()));

  cut_action = new QAction(QIcon(":/images/cut.png"), "剪切", this);
  cut_action->setShortcut(tr("ctrl+x"));
  cut_action->setStatusTip("剪切");
  connect(cut_action, SIGNAL(triggered(bool)), text_edit, SLOT(cut()));

  about_action = new QAction("关于", this);
  about_action->setShortcut(tr("ctrl+a"));
  connect(about_action, SIGNAL(triggered(bool)), this, SLOT(slot_about()));

  background_action = new QAction("背景", this);
  background_action->setShortcut(tr("ctrl+b"));
  background_action->setStatusTip("背景");
  connect(background_action, SIGNAL(triggered(bool)), this,
          SLOT(slot_background()));
}

void TextGui::create_menu() {
  auto menuBar = this->menuBar();
  auto fileMenu = menuBar->addMenu("文件");
  fileMenu->addAction(new_action);
  fileMenu->addAction(open_action);
  fileMenu->addAction(save_action);
  fileMenu->addSeparator();
  fileMenu->addAction(exit_action);

  auto editMenu = menuBar->addMenu("编辑");
  editMenu->addAction(copy_action);
  editMenu->addAction(paste_action);
  editMenu->addAction(cut_action);
  editMenu->addAction(background_action);

  auto aboutMenu = menuBar->addMenu("关于");
  aboutMenu->addAction(about_action);
}

void TextGui::create_toolBar() {
  auto fileToolBar = this->addToolBar("文件");
  fileToolBar->addAction(new_action);
  fileToolBar->addAction(open_action);
  fileToolBar->addAction(save_action);

  auto editEditToolBar = this->addToolBar("编辑");
  editEditToolBar->addAction(copy_action);
  editEditToolBar->addAction(paste_action);
  editEditToolBar->addAction(cut_action);
}

void TextGui::slot_new() {
  auto new_window = new TextGui(nullptr);
  new_window->move(x() + 50, y() + 50);
  new_window->show();
  set_winCount(get_winCount() + 1);
  qDebug() << "slot_new: " << get_winCount() << Qt::endl;
}

void TextGui::slot_open() {
  auto path = QFileDialog::getOpenFileName(this, "选择文件", "..","C++ file(*.cpp);;all(*.*)");
  if (!path.trimmed().isEmpty()) {
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
      QTextStream stream(&file);
      QString str;
      str = stream.readAll();
      text_edit->insertPlainText(str);
    }
    file.close();
  }
}

void TextGui::slot_save() {
  auto path = QFileDialog::getSaveFileName(this, "选择文件", "..","C++ file(*.cpp);;all(*.*)");
  if (!path.trimmed().isEmpty()) {
    QFile file(path);
    if (file.open(QIODevice::ReadWrite)) {
      QTextStream out(&file);
      QString str = text_edit->toPlainText();
      if (!str.isEmpty())
        out << str;
    }
    file.close();
  }
}

void TextGui::slot_background() {
  auto color = QColorDialog::getColor(Qt::red, this);
  if (color.isValid()) {
    auto pale = text_edit->palette();
    pale.setColor(QPalette::Base, color);
    text_edit->setPalette(pale);
  }
}

void TextGui::slot_about() { QMessageBox::about(this, "关于", "我的记事本"); }

int TextGui::get_winCount() { return winCount; }
void TextGui::set_winCount(int n) { winCount = n; }