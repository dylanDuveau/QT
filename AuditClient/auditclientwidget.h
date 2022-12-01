#ifndef AUDITCLIENTWIDGET_H
#define AUDITCLIENTWIDGET_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AuditClientWidget; }
QT_END_NAMESPACE

class AuditClientWidget : public QMainWindow
{
    Q_OBJECT

public:
    AuditClientWidget(QWidget *parent = nullptr);
    ~AuditClientWidget();

private:
    Ui::AuditClientWidget *ui;
};
#endif // AUDITCLIENTWIDGET_H
