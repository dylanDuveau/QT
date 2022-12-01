#include "serveurdab.h"
#include "ui_serveurdab.h"

ServeurDAB::ServeurDAB(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServeurDAB)
{
    ui->setupUi(this);
}

ServeurDAB::~ServeurDAB()
{
    delete ui;
}

