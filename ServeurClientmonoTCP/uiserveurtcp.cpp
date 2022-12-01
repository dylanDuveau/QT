#include "uiserveurtcp.h"
#include "ui_uiserveurtcp.h"

UIServeurTCP::UIServeurTCP(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UIServeurTCP)
{
    ui->setupUi(this);
    connect(&sockServ,&QTcpServer::newConnection, this, &UIServeurTCP::onQTcpServernewConnection);
    connect(&sockServ,&QTcpServer::acceptError, this, &UIServeurTCP::onQTcpServeracceptError);
}

UIServeurTCP::~UIServeurTCP()
{
    delete ui;
}


void UIServeurTCP::on_pushButton_Quitter_clicked()
{
    close();
}


void UIServeurTCP::on_pushButton_Lancer_clicked()
{
    if(sockServ.listen(QHostAddress::Any, ui->spinBoxPort->value())){
        ui->textEditMessage->append("Bonjour runil");
    }else{
        ui->textEditMessage->append("pb lancement");
    }
}

void UIServeurTCP::onQTcpServeracceptError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError); // le paramètre n'est pas utilisé dans cette méthode
    ui->textEditMessage->append(sockServ.errorString());
}

void UIServeurTCP::onQTcpServernewConnection()
{
    ui->textEditMessage->append("nouvelle connexion");
    //récupération de la socket de communication avec le client
    sockClient=sockServ.nextPendingConnection();

    connect(sockClient, &QTcpSocket::connected,this,&UIServeurTCP::onQTcpSocketconnected);
    connect(sockClient, &QTcpSocket::disconnected,this,&UIServeurTCP::onQTcpSocketdisconnected);
    connect(sockClient, &QTcpSocket::readyRead,this,&UIServeurTCP::onQTcpSocketreadyRead);
    connect(sockClient, &QTcpSocket::stateChanged,this,&UIServeurTCP::onQTcpSocketStateChanged);
    connect(sockClient, &QTcpSocket::errorOccurred,this,&UIServeurTCP::onQTcpSocketErrorOccurred);
    connect(sockClient, &QTcpSocket::hostFound,this,&UIServeurTCP::onQTcpSockethostFound);
    connect(sockClient, &QTcpSocket::aboutToClose,this,&UIServeurTCP::onQTcpSocketaboutToClose);
    connect(sockClient, &QTcpSocket::channelBytesWritten,this,&UIServeurTCP::onQTcpSocketchannelBytesWritten);
    connect(sockClient, &QTcpSocket::channelReadyRead,this,&UIServeurTCP::onQTcpSocketchannelReadyRead);
    connect(sockClient, &QTcpSocket::readChannelFinished,this,&UIServeurTCP::onQTcpSocketreadChannelFinished);
    connect(sockClient, &QTcpSocket::bytesWritten,this,&UIServeurTCP::onQTcpSocketbytesWritten);
    connect(sockClient, &QTcpSocket::destroyed,this,&UIServeurTCP::onQTcpSocketdestroyed);

}


void UIServeurTCP::onQTcpSockethostFound()
{
    ui->textEditMessage->append("host found");
}

void UIServeurTCP::onQTcpSocketconnected()
{
    ui->textEditMessage->append("Un looser est connecter");
}

void UIServeurTCP::onQTcpSocketdisconnected()
{
    ui->textEditMessage->append("Déconnexion du looser ^_^");
}

void UIServeurTCP::onQTcpSocketbytesWritten(qint64 bytes)
{
    ui->textEditMessage->append(QString::number(bytes)+" bytes written on chanel");
}

void UIServeurTCP::onQTcpSocketreadyRead()
{
    QByteArray data;
    QByteArray reponse;
    ui->textEditMessage->append("Dans readyRead");
    //réception message client
    data = sockClient->readAll();
    ui->textEditMessage->append(data);
    //envoyer la reponse
    reponse="Msg reçu : " +data;
    sockClient->write(reponse);
}

void UIServeurTCP::onQTcpSocketdestroyed(QObject *obj)
{
    Q_UNUSED(obj);
    ui->textEditMessage->append("obj destroyed");
}

void UIServeurTCP::onQTcpSocketchannelReadyRead(int channel)
{
    ui->textEditMessage->append("ready read on chanel" +QString::number(channel));
}

void UIServeurTCP::onQTcpSocketchannelBytesWritten(int channel, qint64 bytes)
{
    ui->textEditMessage->append(QString::number(bytes)+" bytes written on chanel"+ QString::number(channel));
}

void UIServeurTCP::onQTcpSocketaboutToClose()
{
    ui->textEditMessage->append("about to close");
}

void UIServeurTCP::onQTcpSocketreadChannelFinished()
{
    ui->textEditMessage->append("Read channel finished");
}

void UIServeurTCP::onQTcpSocketStateChanged(QAbstractSocket::SocketState socketState)
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

void UIServeurTCP::onQTcpSocketErrorOccurred(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError); // le paramètre n'est pas utilisé dans cette méthode
    ui->textEditMessage->append(sockClient->errorString());
}



