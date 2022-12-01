#include "auditclient.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AuditClient w;
    w.show();
    return a.exec();
}
