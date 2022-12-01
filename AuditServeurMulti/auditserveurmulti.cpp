#include "auditserveurmulti.h"
#include "ui_auditserveurmulti.h"

AuditServeurMulti::AuditServeurMulti(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuditServeurMulti)
{
    ui->setupUi(this);
    socketEcouteServeur = new QTcpServer;
    socketEcouteServeur->setMaxPendingConnections(30);
    connect(socketEcouteServeur,&QTcpServer::newConnection, this, &AuditServeurMulti::onQTcpServernewConnection);
    connect(socketEcouteServeur,&QTcpServer::acceptError, this, &AuditServeurMulti::onQTcpServeracceptError);
}

AuditServeurMulti::~AuditServeurMulti()
{
    delete socketEcouteServeur;
    delete ui;
}





void AuditServeurMulti::on_pushButton_Lancer_clicked()
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



void AuditServeurMulti::onQTcpServeracceptError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError); // le paramètre n'est pas utilisé dans cette méthode
    ui->textEditMessage->append(socketEcouteServeur->errorString());
}


void AuditServeurMulti::onQTcpServernewConnection()
{
 QTcpSocket *Client;
    //récupération de la socket de communication avec le client
    Client = socketEcouteServeur->nextPendingConnection();
    connect(Client, &QTcpSocket::connected,this,&AuditServeurMulti::onQTcpSocketconnected);
    connect(Client, &QTcpSocket::disconnected,this,&AuditServeurMulti::onQTcpSocketdisconnected);
    connect(Client, &QTcpSocket::readyRead,this,&AuditServeurMulti::onQTcpSocketreadyRead);
    connect(Client, &QTcpSocket::stateChanged,this,&AuditServeurMulti::onQTcpSocketStateChanged);
    connect(Client, &QTcpSocket::errorOccurred,this,&AuditServeurMulti::onQTcpSocketErrorOccurred);
    connect(Client, &QTcpSocket::hostFound,this,&AuditServeurMulti::onQTcpSockethostFound);
    connect(Client, &QTcpSocket::aboutToClose,this,&AuditServeurMulti::onQTcpSocketaboutToClose);
    connect(Client, &QTcpSocket::channelBytesWritten,this,&::AuditServeurMulti::onQTcpSocketbytesWritten);
    connect(Client, &QTcpSocket::channelReadyRead,this,&::AuditServeurMulti::onQTcpSocketreadyRead);
    connect(Client, &QTcpSocket::bytesWritten,this,&AuditServeurMulti::onQTcpSocketbytesWritten);
    connect(Client, &QTcpSocket::destroyed,this,&::AuditServeurMulti::onQTcpSockethostFound);

  listeSocketDialogueClient.append(Client);
  QProcess *process = new QProcess(this);
  connect(process,&QProcess::readyReadStandardOutput,this,&AuditServeurMulti::onQProcess_readyReadStandardOutput);
  listeProcess.append(process);

   QHostAddress addresseClient = Client->peerAddress();
    ui->textEditMessage->append("connexion de : "+Client->peerAddress().toString());
   }





void AuditServeurMulti::onQTcpSockethostFound()
{
    ui->textEditMessage->append("host found");
}

void AuditServeurMulti::onQTcpSocketconnected()
{
    ui->textEditMessage->append("Un looser est connecter");

}

void AuditServeurMulti::onQTcpSocketdisconnected()
{
    QTcpSocket *client =qobject_cast<QTcpSocket*>(sender());
    int indexClient = listeSocketDialogueClient.indexOf(client);
    disconnect(client,nullptr,this,nullptr);
    listeProcess.removeAt(indexClient);
    listeSocketDialogueClient.removeOne(client);
    client->deleteLater();
    ui->textEditMessage->append("Client détconnecté");
}

void AuditServeurMulti::onQTcpSocketreadyRead()
{
  QTcpSocket *client =qobject_cast<QTcpSocket*>(sender());
  int indexClient = listeSocketDialogueClient.indexOf(client);
  QProcess *process = listeProcess.at(indexClient);
  QChar commande;
  QString reponse;

    if(client->bytesAvailable())
    {
        QByteArray tampon = client->readAll();
        commande = tampon.at(0);
        QString message = "Commande reçu de " + client->peerAddress().toString() + " :";
        message += commande;
        ui->textEditMessage->append(message);
        switch (commande.toLatin1())
        {
        case 'u' : reponse = getenv("USER");
            client->write(reponse.toLatin1());
            break;

        case 'a' :
            process->start("uname",QStringList("-p"));
            break;

        case 'c' : reponse = QHostInfo::localHostName();
            client->write(reponse.toLatin1());
            break;

        case 'o' :
            process->start("uname");
            break;
        }
    }

}

void AuditServeurMulti::onQTcpSocketErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError); // le paramètre n'est pas utilisé dans cette méthode
    QTcpSocket *client=qobject_cast<QTcpSocket*>(sender());
    ui->textEditMessage->append("client"+client->errorString());
}


void AuditServeurMulti::onQTcpSocketStateChanged(QAbstractSocket::SocketState socketState)
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

void AuditServeurMulti::onQTcpSocketaboutToClose()
{
    ui->textEditMessage->append("host found");
}

void AuditServeurMulti::onQTcpSocketbytesWritten(qint64 bytes)
{
    ui->textEditMessage->append(QString::number(bytes)+" bytes written on chanel");
}

void AuditServeurMulti::onQProcess_readyReadStandardOutput()
{
   QProcess * process =qobject_cast<QProcess*>(sender());
   int indexProcess = listeProcess.indexOf(process);
   QTcpSocket *client =listeSocketDialogueClient.at(indexProcess);
   QString reponse = process->readAllStandardOutput();
       if(!reponse.isEmpty())
          client->write(reponse.toLatin1());

}













void AuditServeurMulti::on_pushButton_Quitter_clicked()
{

}
