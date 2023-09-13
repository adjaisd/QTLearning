#include <QApplication>
#include "LcdNumber.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    LcdNumber lcdNumber;
    lcdNumber.show();
    return a.exec();
}
