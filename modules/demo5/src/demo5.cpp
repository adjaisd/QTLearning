#include <QApplication>
#include <QDir>
#include <QTranslator>
#include "MessageGUI.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QTranslator trans;
  if (trans.load(":/" + QLocale().name() + ".qm")) {
    QApplication::installTranslator(&trans);
    qDebug() << "Load successfully. " << Qt::endl;
  } else {
    qDebug() << "Failed to load. " << QLocale::system().name() << Qt::endl;
  }
  MessageGUI messageGui;
  messageGui.show();
  return a.exec();
}