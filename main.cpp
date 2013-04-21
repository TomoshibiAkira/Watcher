#include <QApplication>
#include "watcher.h"
#include "header.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    filePick();
    Watcher w;
    w.show();
    return a.exec();
}
