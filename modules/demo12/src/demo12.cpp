#include <QApplication>
#include "ItemGui.h"

int main(int argc, char*argv[]) {
  QApplication a(argc, argv);
  ItemGui itemGui;
  itemGui.show();
  return a.exec();
}