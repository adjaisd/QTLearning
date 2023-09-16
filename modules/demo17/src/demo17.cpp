#include <QApplication>
#include "SoundGui.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  SoundGui soundGui;
  soundGui.show();
  return a.exec();
}