#include "auditserveurmono.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuditServeurMono w;
    w.show();
    return a.exec();
}
