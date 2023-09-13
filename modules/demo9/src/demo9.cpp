#include <QApplication>
#include "LayoutGui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    LayoutGui layoutGui;
    layoutGui.show();
    return a.exec();
}
