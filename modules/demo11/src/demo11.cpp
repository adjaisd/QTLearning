#include <QApplication>
#include "MapGui.h"

int main(int argc, char*argv[]) {
  QApplication a(argc, argv);
  MapGui m;
  m.show();
  return a.exec();
}