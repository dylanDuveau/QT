#include "auditclientwidget.h"
#include "ui_auditclientwidget.h"

AuditClientWidget::AuditClientWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuditClientWidget)
{
    ui->setupUi(this);
}

AuditClientWidget::~AuditClientWidget()
{
    delete ui;
}

