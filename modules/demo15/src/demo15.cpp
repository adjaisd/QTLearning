#include <QApplication>
#include "MouseEventGui.h"
#include "KeyEventGui.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
#define eventChoice 2
#if eventChoice == 1
  MouseEventGui mouseEventGui;
  mouseEventGui.show();
#elif eventChoice == 2
  KeyEventGui keyEventGui;
  keyEventGui.show();
#endif
  return a.exec();
}