#ifndef WIDGGETUSB202_H
#define WIDGGETUSB202_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class WidggetUSB202; }
QT_END_NAMESPACE

class WidggetUSB202 : public QWidget
{
    Q_OBJECT

public:
    WidggetUSB202(QWidget *parent = nullptr);
    ~WidggetUSB202();

private:
    Ui::WidggetUSB202 *ui;
};
#endif // WIDGGETUSB202_H
