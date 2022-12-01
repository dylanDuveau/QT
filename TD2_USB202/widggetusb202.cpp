#include "widggetusb202.h"
#include "ui_widggetusb202.h"

WidggetUSB202::WidggetUSB202(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidggetUSB202)
{
    ui->setupUi(this);
}

WidggetUSB202::~WidggetUSB202()
{
    delete ui;
}

