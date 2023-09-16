#include "SignalGUI.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  SignalGUI signalGui;
  signalGui.show();
  return a.exec();
}