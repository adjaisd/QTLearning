#include <QApplication>
#include "PosSizeGui.h"

int main(int argc, char *argv[]) {
    // QT所有的对象需要在QApplication之后创建
    QApplication a(argc, argv);
    PosSizeGui posSizeGui(nullptr);
    posSizeGui.show();
    return QApplication::exec();
}
