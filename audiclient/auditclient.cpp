#include "auditclient.h"
#include "ui_auditclient.h"
#include <QDebug>

AuditClient::AuditClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuditClient)
{
    socketDeDiaglogueAvecServeur = new QTcpSocket(this);
    ui->setupUi(this);
    ui->groupBoxInformationsClient->setDisabled(true);
    connect(socketDeDiaglogueAvecServeur, &QTcpSocket::connected,this,&AuditClient::onQTcpSocketconnected);
    connect(socketDeDiaglogueAvecServeur, &QTcpSocket::disconnected,this,&AuditClient::onQTcpSocketdisconnected);
    connect(socketDeDiaglogueAvecServeur, &QTcpSocket::readyRead,this,&AuditClient::onQTcpSocketreadyRead);
    connect(socketDeDiaglogueAvecServeur, &QTcpSocket::stateChanged,this,&AuditClient::onQTcpSocketStateChanged);
    connect(socketDeDiaglogueAvecServeur, &QTcpSocket::errorOccurred,this,&AuditClient::onQTcpSocketErrorOccurred);
    connect(socketDeDiaglogueAvecServeur, &QTcpSocket::hostFound,this,&AuditClient::onQTcpSockethostFound);
    connect(socketDeDiaglogueAvecServeur, &QTcpSocket::aboutToClose,this,&AuditClient::onQTcpSocketaboutToClose);
    connect(socketDeDiaglogueAvecServeur, &QTcpSocket::channelBytesWritten,this,&AuditClient::onQTcpSocketchannelBytesWritten);
    connect(socketDeDiaglogueAvecServeur, &QTcpSocket::channelReadyRead,this,&AuditClient::onQTcpSocketchannelReadyRead);
    connect(socketDeDiaglogueAvecServeur, &QTcpSocket::readChannelFinished,this,&AuditClient::onQTcpSocketreadChannelFinished);
    connect(socketDeDiaglogueAvecServeur, &QTcpSocket::bytesWritten,this,&AuditClient::onQTcpSocketbytesWritten);
    connect(socketDeDiaglogueAvecServeur, &QTcpSocket::destroyed,this,&AuditClient::onQTcpSocketdestroyed);
}

AuditClient::~AuditClient()
{
    if(socketDeDiaglogueAvecServeur != nullptr){
        socketDeDiaglogueAvecServeur->close();
        delete socketDeDialogueAvecServeur;
    }
    delete ui;
}


void AuditClient::on_pushButtonQuitter_clicked()
{
    close();
}


void AuditClient::on_pushButtonConnexion_clicked()
{
    if(ui->pushButtonConnexion->text()=="Connexion"){
        socketDeDiaglogueAvecServeur->connectToHost(ui->lineEditAdresseIP->text(),ui->lineEditPort->text().toInt());
    }else{
        socketDeDiaglogueAvecServeur->disconnectFromHost();
    }
}


void AuditClient::on_pushButtonArchitecture_clicked()
{
    typeDeDemande="a";
    socketDeDiaglogueAvecServeur->write(typeDeDemande.toLatin1());
}


void AuditClient::on_pushButtonOs_clicked()
{
    typeDeDemande="o";
    socketDeDiaglogueAvecServeur->write(typeDeDemande.toLatin1());
}


void AuditClient::on_pushButtonUtilisateur_clicked()
{
    typeDeDemande="u";
    socketDeDiaglogueAvecServeur->write(typeDeDemande.toLatin1());
}


void AuditClient::on_pushButtonOrdinateur_clicked()
{
    typeDeDemande="c";
    socketDeDiaglogueAvecServeur->write(typeDeDemande.toLatin1());
}

void AuditClient::onQTcpSockethostFound()
{
    ui->textEditEtat->append("host found");
}

void AuditClient::onQTcpSocketconnected()
{
    ui->textEditEtat->append("Connected");
    ui->pushButtonConnexion->setText("Déconnexion");
    ui->lineEditAdresseIP->setEnabled(false);
    ui->lineEditPort->setEnabled(false);
    ui->groupBoxInformationsClient->setEnabled(true);

    ui->pushButtonOs->setEnabled(true);
    ui->pushButtonArchitecture->setEnabled(true);
    ui->pushButtonOrdinateur->setEnabled(true);
    ui->pushButtonConnexion->setEnabled(true);
}

void AuditClient::onQTcpSocketdisconnected()
{
     ui->textEditEtat->append("Disconnected");
    ui->lineEditAdresseIP->setEnabled(true);
    ui->lineEditAdresseIP->setEnabled(true);
    ui->pushButtonConnexion->setText("Connexion");
    ui->groupBoxInformationsClient->setEnabled(false);
}

void AuditClient::onQTcpSocketbytesWritten(qint64 bytes)
{
     ui->textEditEtat->append(QString::number(bytes)+" bytes written on chanel");
}

void AuditClient::onQTcpSocketreadyRead()
{
    QByteArray buffer;
    if(socketDeDiaglogueAvecServeur->bytesAvailable()>0){
        buffer = socketDeDiaglogueAvecServeur -> readAll();
        if(typeDeDemande=="u"){
            ui->lineEditUtilisateur->setText(buffer.data());
        }
        if(typeDeDemande=="c"){
            ui->lineEditOrdinateur->setText(buffer.data());
        }
        if(typeDeDemande=="o"){
            ui->lineEditOs->setText(buffer.data());
        }
        if(typeDeDemande=="a"){
            ui->lineEditArchitecture->setText(buffer.data());
        }
    }
}

void AuditClient::onQTcpSocketdestroyed(QObject *obj)
{
    Q_UNUSED(obj);
    ui->textEditEtat->append("obj destroyed");
}

void AuditClient::onQTcpSocketchannelReadyRead(int channel)
{
     ui->textEditEtat->append("ready read on chanel" +QString::number(channel));
}

void AuditClient::onQTcpSocketchannelBytesWritten(int channel, qint64 bytes)
{
 ui->textEditEtat->append(QString::number(bytes)+" bytes written on chanel"+ QString::number(channel));
}

void AuditClient::onQTcpSocketaboutToClose()
{
     ui->textEditEtat->append("about to close");
}

void AuditClient::onQTcpSocketreadChannelFinished()
{
    ui->textEditEtat->append("Read channel finished");
}

void AuditClient::onQTcpSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    switch (socketState) {
    case QAbstractSocket::UnconnectedState:
        ui ->textEditEtat->append("The socket is not connected.");
        break;
    case QAbstractSocket::HostLookupState:
        ui ->textEditEtat->append("The socket is performing a host name lookup.");
        break;
    case QAbstractSocket::ConnectingState:
        ui ->textEditEtat->append("The socket has started establishing a connection.");
        break;
    case QAbstractSocket::ConnectedState:
        ui ->textEditEtat->append("A connection is established.");
        break;
    case QAbstractSocket::BoundState:
        ui ->textEditEtat->append("The socket is bound to an address and port.");
        break;
    case QAbstractSocket::ClosingState:
        ui ->textEditEtat->append("The socket is about to close (data may still be waiting to be written).");
        break;
    case QAbstractSocket::ListeningState:
        ui ->textEditEtat->append("For internal use only.");
        break;
    }
}

void AuditClient::onQTcpSocketErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError); // le paramètre n'est pas utilisé dans cette méthode
    ui->textEditEtat->append(socketDeDiaglogueAvecServeur->errorString());
}

