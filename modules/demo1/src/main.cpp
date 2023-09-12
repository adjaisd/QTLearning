#include <QApplication>
#include "winserver.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    WinServer w;
    w.show();
    return a.exec();
}
