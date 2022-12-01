#include "uiserveurtcp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UIServeurTCP w;
    w.show();
    return a.exec();
}
