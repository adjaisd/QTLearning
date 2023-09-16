#include <QApplication>
#include "SettingsGui.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  SettingsGui settingsGui;
  settingsGui.show();
  return a.exec();
}