#include <QApplication>
#include "TextGui.h"

int TextGui::winCount = 1;
int main(int argc, char*argv[]) {
  QApplication a(argc, argv);
  TextGui textGui(nullptr);
  textGui.show();
  return a.exec();
}