#include <QApplication>
#include "winserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WinServer w;
    w.show();

//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();
    return a.exec();
}
