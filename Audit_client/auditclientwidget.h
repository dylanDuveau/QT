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

private slots:
    void on_pushButtonConnexion_clicked();

    void on_pushButtonQuitter_clicked();

    void on_pushButtonOrdinateur_clicked();

    void on_pushButtonUtilisateur_clicked();

    void on_pushButtonArchitecture_clicked();

    void on_pushButtonOS_clicked();

private:
    Ui::AuditClientWidget *ui;
};
#endif // AUDITCLIENTWIDGET_H
