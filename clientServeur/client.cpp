#include "client.h"
#include "ui_client.h"
#include <QDebug>

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);
    //desactiver le bouton envoyer
    ui->pushButton_Envoyer->setDisabled(true);
    //desactiver le text a envoyer
    ui->lineEditMessage->setDisabled(true);
    //association signal/slot pour socVersServeur
    connect(&sockVersServeur, &QTcpSocket::connected,this,&client::onQTcpSocketConnect);
    connect(&sockVersServeur, &QTcpSocket::disconnected,this,&client::onQTcpSocketDisconnect);
    connect(&sockVersServeur, &QTcpSocket::readyRead,this,&client::onQTcpSocketReadyRead);
    connect(&sockVersServeur, &QTcpSocket::stateChanged,this,&client::onQTcpSocketStateChanged);
    connect(&sockVersServeur, &QTcpSocket::errorOccurred,this,&client::onQTcpSocketErrorOccurred);
}

client::~client()
{
    delete ui;
}



void client::on_pushButton_clicked()
{
    sockVersServeur.connectToHost(ui->lineEdit_IPServeur->text(),ui->spinBox->value());
}


void client::on_pushButton_Envoyer_clicked()
{
    sockVersServeur.write(ui->lineEditMessage->text().toUtf8());
}

void client::onQTcpSocketConnect()
{
    qDebug()<<"connected";
    //activer envoyer
    ui->pushButton_Envoyer->setDisabled(false);
    //activer message
    ui->lineEditMessage->setDisabled(false);

    //desactiver le bouton connexion
    ui->pushButton->setDisabled(true);
    //desactiver le port
    ui->spinBox->setDisabled(true);
    //desactiver ip
    ui->lineEdit_IPServeur->setDisabled(true);
}

void client::onQTcpSocketDisconnect()
{
    qDebug()<<"disconnected";
    //desactiver envoyer
    ui->pushButton_Envoyer->setDisabled(true);
    //desactiver message
    ui->lineEditMessage->setDisabled(true);

    //activer le bouton connexion
    ui->pushButton->setDisabled(false);
    //activer le port
    ui->spinBox->setDisabled(false);
    //activer ip
    ui->lineEdit_IPServeur->setDisabled(false);
}

void client::onQTcpSocketReadyRead()
{
    QByteArray reponse;
    reponse = sockVersServeur.readAll();
    ui->textEdit->append(reponse);
}

void client::onQTcpSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    switch (socketState) {
    case QAbstractSocket::UnconnectedState:
        ui ->textEdit->append("The socket is not connected.");
        break;
    case QAbstractSocket::HostLookupState:
        ui ->textEdit->append("The socket is performing a host name lookup.");
        break;
    case QAbstractSocket::ConnectingState:
        ui ->textEdit->append("The socket has started establishing a connection.");
        break;
    case QAbstractSocket::ConnectedState:
        ui ->textEdit->append("A connection is established.");
        break;
    case QAbstractSocket::BoundState:
        ui ->textEdit->append("The socket is bound to an address and port.");
        break;
    case QAbstractSocket::ClosingState:
        ui ->textEdit->append("The socket is about to close (data may still be waiting to be written).");
        break;
    case QAbstractSocket::ListeningState:
        ui ->textEdit->append("For internal use only.");
        break;
    }
}

void client::onQTcpSocketErrorOccurred(QAbstractSocket::SocketError socketError)
{
    ui->textEdit->append(sockVersServeur.errorString());
}

