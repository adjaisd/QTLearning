#include <QApplication>
#include "TableGUI.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    TableGUI tableGui;
    tableGui.show();
    return a.exec();
}
