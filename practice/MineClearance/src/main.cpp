#include "CustomGameDialog.h"
#include "HeroDialog.h"
#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
#define choice 3
#if choice == 1 // 测试CustomGameDialog
  CustomGameDialog customGameDialog;
  customGameDialog.show();
#elif choice == 2 // 测试HeroDialog
  HeroDialog heroDialog;
  heroDialog.show();
#elif choice == 3
  MainWindow mainWindow(nullptr);
  mainWindow.show();
#endif
  return a.exec();
}