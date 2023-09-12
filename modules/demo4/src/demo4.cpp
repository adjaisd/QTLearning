#include <QApplication>
#include "Input.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Input input;
    input.show();
    return a.exec();
}