#include "auditserveurmulti.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuditServeurMulti w;
    w.show();
    return a.exec();
}
