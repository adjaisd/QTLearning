#include <QApplication>
#include "QQ.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QQ qq;
    qq.show();
    return a.exec();
}