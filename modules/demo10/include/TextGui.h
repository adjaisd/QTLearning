#ifndef TEXTGUI_H
#define TEXTGUI_H

#include <QAction>
#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QTextEdit>
#include <QTextStream>
#include <QToolBar>
#include <QCloseEvent>

class TextGui : public QMainWindow {
  Q_OBJECT
public:
  explicit TextGui(QWidget * = nullptr);
  ~TextGui() noexcept override;
  void create_action();
  void create_menu();
  void create_toolBar();
protected:
  void closeEvent(QCloseEvent *) override;
public slots:
  void slot_new();
  void slot_open();
  void slot_save();
  void slot_background();
  void slot_about();

private:
  QTextEdit *text_edit;
  QAction *new_action{};
  QAction *open_action{};
  QAction *save_action{};
  QAction *exit_action{};
  QAction *copy_action{};
  QAction *paste_action{};
  QAction *cut_action{};
  QAction *about_action{};
  QAction *background_action{};
public:
  static int get_winCount();
  static void set_winCount(int);
  static int winCount;
};

#endif // TEXTGUI_H
