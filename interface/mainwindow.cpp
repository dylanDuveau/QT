#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButtonEnvoyer->setDisabled(true);
    ui->lineEdit_TexteAEnvoyer->setDisabled(true);
    connect(&sockVersServeur,
            &QTcpSocket::connected,
            this,
            &::MainWindow::QTcpSocketConnected);
    connect(&sockVersServeur,
            &QTcpSocket::disconnected,
            this,
            &::MainWindow::QTcpSocketConnected);
    connect(&sockVersServeur,
            &QTcpSocket::readyRead,
            this,
            &::MainWindow::QTcpSocketConnected);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonEnvoyer_clicked()
{
    sockVersServeur.connectToHost(ui->lineEdit_IPServeur->text(),ui->spinBox->value());
}

void MainWindow::QTcpSocketEnvoyer()
{
    sockVersServeur.write(ui->lineEdit_Texte->text().toUtf8());
}

void MainWindow::QTcpSocketConnected()
{
    qDebug()<<"connected";
    ui->pushButtonEnvoyer->setDisabled(false);
    ui->lineEdit_Texte->setDisabled(false);
    ui->pushButtonConnexion->setDisabled(true);
    ui->spinBox->setDisabled(true);
}


void MainWindow::on_pushButtonConnexion_clicked()
{
    qDebug()<<"disconnected";
    ui->pushButtonEnvoyer->setDisabled(true);
    ui->lineEdit_Texte->setDisabled(true);
    ui->pushButtonConnexion->setDisabled(false);
    ui->spinBox->setDisabled(false);
}

