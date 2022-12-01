#include "auditserveurmono.h"
#include "ui_auditserveurmono.h"

AuditServeurMono::AuditServeurMono(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuditServeurMono)
    ,socketDialogueClient(nullptr)
{
    ui->setupUi(this);
    socketEcouteServeur = new QTcpServer;
    socketEcouteServeur->setMaxPendingConnections(2);
    connect(socketEcouteServeur,&QTcpServer::newConnection, this, &AuditServeurMono::onQTcpServernewConnection);
    connect(socketEcouteServeur,&QTcpServer::acceptError, this, &AuditServeurMono::onQTcpServeracceptError);
    process = new QProcess(this);
    connect(process,&QProcess::readyReadStandardOutput,this,&AuditServeurMono::onQProcess_readyReadStandardOutput);
}

AuditServeurMono::~AuditServeurMono()
{
    if(socketDialogueClient != nullptr)
     {
         socketDialogueClient ->close();
         delete socketDialogueClient;
     }
     delete socketEcouteServeur;
     delete ui;
}


void AuditServeurMono::on_pushButton_Lancer_clicked()
{
    if(!socketEcouteServeur->listen(QHostAddress::Any, ui->spinBoxPort->value()))
       {
           QString message = "Impossible de démarrer le serveur" + socketEcouteServeur->errorString();
           ui->textEditMessage->append(message);
       }
       else
       {
           QList<QHostAddress> listeAdreses = QNetworkInterface::allAddresses();
           QList<QHostAddress>::iterator it;
           for (it = listeAdreses.begin(); it != listeAdreses.end(); it++)
           {
               if(it->toIPv4Address())
                   ui->textEditMessage->append("Adrese serveur :" + it->toString());
           }
           ui->textEditMessage->append("N° du port : " + QString::number(socketEcouteServeur->serverPort()));
           ui->pushButton_Lancer->setEnabled(false);
           ui->spinBoxPort->setEnabled(false);
       }
}



void AuditServeurMono::onQTcpServeracceptError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError); // le paramètre n'est pas utilisé dans cette méthode
    ui->textEditMessage->append(socketEcouteServeur->errorString());
}


void AuditServeurMono::onQTcpServernewConnection()
{
   ui->textEditMessage->append("nouvelle connexion");
    if(socketDialogueClient != nullptr)
    {
        socketDialogueClient->close();
        delete socketDialogueClient;
    }
    //récupération de la socket de communication avec le client
    socketDialogueClient=socketEcouteServeur->nextPendingConnection();
    connect(socketDialogueClient, &QTcpSocket::connected,this,&AuditServeurMono::onQTcpSocketconnected);
    connect(socketDialogueClient, &QTcpSocket::disconnected,this,&AuditServeurMono::onQTcpSocketdisconnected);
    connect(socketDialogueClient, &QTcpSocket::readyRead,this,&AuditServeurMono::onQTcpSocketreadyRead);
    connect(socketDialogueClient, &QTcpSocket::stateChanged,this,&AuditServeurMono::onQTcpSocketStateChanged);
    connect(socketDialogueClient, &QTcpSocket::errorOccurred,this,&AuditServeurMono::onQTcpSocketErrorOccurred);
    connect(socketDialogueClient, &QTcpSocket::hostFound,this,&AuditServeurMono::onQTcpSockethostFound);
    connect(socketDialogueClient, &QTcpSocket::aboutToClose,this,&AuditServeurMono::onQTcpSocketaboutToClose);
    connect(socketDialogueClient, &QTcpSocket::channelBytesWritten,this,&::AuditServeurMono::onQTcpSocketbytesWritten);
    connect(socketDialogueClient, &QTcpSocket::channelReadyRead,this,&::AuditServeurMono::onQTcpSocketreadyRead);
    connect(socketDialogueClient, &QTcpSocket::bytesWritten,this,&AuditServeurMono::onQTcpSocketbytesWritten);
    connect(socketDialogueClient, &QTcpSocket::destroyed,this,&::AuditServeurMono::onQTcpSockethostFound);

   QHostAddress addresseClient = socketDialogueClient->peerAddress();
    ui->textEditMessage->append("connexion de : "+socketDialogueClient->peerAddress().toString());
   }





void AuditServeurMono::onQTcpSockethostFound()
{
    ui->textEditMessage->append("host found");
}

void AuditServeurMono::onQTcpSocketconnected()
{
    ui->textEditMessage->append("Un looser est connecter");

}

void AuditServeurMono::onQTcpSocketdisconnected()
{
    disconnect(socketDialogueClient,nullptr,this,nullptr);
    socketDialogueClient->deleteLater();
    socketDialogueClient = nullptr;
    ui->textEditMessage->append("Client détconnecté");
}

void AuditServeurMono::onQTcpSocketreadyRead()
{
    QChar commande;
    QString reponse;
    if(socketDialogueClient->bytesAvailable())
    {
        QByteArray tampon = socketDialogueClient->readAll();
        commande = tampon.at(0);
        QString message = "Commande reçu de " + socketDialogueClient->peerAddress().toString() + " :";
        message += commande;
        ui->textEditMessage->append(message);
        switch (commande.toLatin1())
        {
        case 'u' : reponse = getenv("USER");
            socketDialogueClient->write(reponse.toLatin1());
            break;

        case 'a' :
            process->start("uname",QStringList("-p"));
            break;

        case 'c' : reponse = QHostInfo::localHostName();
            socketDialogueClient->write(reponse.toLatin1());
            break;

        case 'o' :
            process->start("uname");
            break;
        }
    }

}

void AuditServeurMono::onQTcpSocketErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError); // le paramètre n'est pas utilisé dans cette méthode
    ui->textEditMessage->append(socketEcouteServeur->errorString());
}


void AuditServeurMono::onQTcpSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    switch (socketState) {
       case QAbstractSocket::UnconnectedState:
           ui ->textEditMessage->append("The socket is not connected.");
           break;
       case QAbstractSocket::HostLookupState:
           ui ->textEditMessage->append("The socket is performing a host name lookup.");
           break;
       case QAbstractSocket::ConnectingState:
           ui ->textEditMessage->append("The socket has started establishing a connection.");
           break;
       case QAbstractSocket::ConnectedState:
           ui ->textEditMessage->append("A connection is established.");
           break;
       case QAbstractSocket::BoundState:
           ui ->textEditMessage->append("The socket is bound to an address and port.");
           break;
       case QAbstractSocket::ClosingState:
           ui ->textEditMessage->append("The socket is about to close (data may still be waiting to be written).");
           break;
       case QAbstractSocket::ListeningState:
           ui ->textEditMessage->append("For internal use only.");
           break;
       }
}

void AuditServeurMono::onQTcpSocketaboutToClose()
{
    ui->textEditMessage->append("host found");
}

void AuditServeurMono::onQTcpSocketbytesWritten(qint64 bytes)
{
    ui->textEditMessage->append(QString::number(bytes)+" bytes written on chanel");
}

void AuditServeurMono::onQProcess_readyReadStandardOutput()
{
    QString reponse = process->readAllStandardOutput();
        if(!reponse.isEmpty())
            socketDialogueClient->write(reponse.toLatin1());
}













void AuditServeurMono::on_pushButton_Quitter_clicked()
{

}

