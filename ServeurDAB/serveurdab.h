#ifndef SERVEURDAB_H
#define SERVEURDAB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ServeurDAB; }
QT_END_NAMESPACE

class ServeurDAB : public QWidget
{
    Q_OBJECT

public:
    ServeurDAB(QWidget *parent = nullptr);
    ~ServeurDAB();

private:
    Ui::ServeurDAB *ui;
};
#endif // SERVEURDAB_H
