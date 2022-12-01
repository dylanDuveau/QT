#include "serveurdab.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServeurDAB w;
    w.show();
    return a.exec();
}
