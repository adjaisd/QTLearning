#include <QApplication>
#include "dialogTest.h"

int main(int argc, char *argv[]) {
    // QT所有的对象需要在QApplication之后创建
    QApplication a(argc, argv);
    DialogTest d(nullptr);
    d.show();
    return QApplication::exec();
}
