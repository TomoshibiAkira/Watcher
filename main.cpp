#include <QApplication>
#include "watcher.h"

//too long to put all the reading file function into main.cpp
#include "header.cpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //picking file and bulid tree
    filePick();

    Watcher w;
    w.show();
    return a.exec();
}
