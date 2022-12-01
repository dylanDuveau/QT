#include "uiserveurtcp.h"
#include "ui_uiserveurtcp.h"

UiServeurTcp::UiServeurTcp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UiServeurTcp)
{
    ui->setupUi(this);
    connect(&sockserv::newConnection,&QTcpServer::onQTcpConnection)
}

UiServeurTcp::~UiServeurTcp()
{
    delete ui;
}

void UiServeurTcp::onQTcpServerNewConnection()
{
    connect(socKClient, &QTcpSocket::connected,this,&UiServeurTcp::onQTcpSocketconnected);
    connect(socKClient, &QTcpSocket::disconnected,this,&UiServeurTcp::onQTcpSocketdisconnected);
    connect(socKClient, &QTcpSocket::readyRead,this,&UiServeurTcp::onQTcpSocketreadyRead);
    connect(socKClient, &QTcpSocket::stateChanged,this,&UiServeurTcp::onQTcpSocketStateChanged);
    connect(socKClient, &QTcpSocket::errorOccurred,this,&UiServeurTcp::onQTcpSocketErrorOccurred);
    connect(socKClient, &QTcpSocket::hostFound,this,&UiServeurTcp::onQTcpSockethostFound);
    connect(socKClient, &QTcpSocket::aboutToClose,this,&UiServeurTcp::onQTcpSocketaboutToClose);
    connect(socKClient, &QTcpSocket::channelBytesWritten,this,&UiServeurTcp::onQTcpSocketchannelBytesWritten);
    connect(socKClient, &QTcpSocket::channelReadyRead,this,&UiServeurTcp::onQTcpSocketchannelReadyRead);
    connect(socKClient, &QTcpSocket::readChannelFinished,this,&UiServeurTcp::onQTcpSocketreadChannelFinished);
    connect(socKClient, &QTcpSocket::bytesWritten,this,&UiServeurTcp::onQTcpSocketbytesWritten);
    connect(socKClient, &QTcpSocket::destroyed,this,&UiServeurTcp::onQTcpSocketdestroyed);
    //multi client

    listeSockClients.append(socKClient);

}




void UiServeurTcp::on_pushButtonLancer_clicked()
{
    if(socketServ.listen(QHostAddress::Any, ui ->spinBoxPort-> value())
    {
            ui ->textEdiMessages ->append("lancement ok ");
}
            else {
            ui->TextEditMessages ->append("pas ok");
}
}


            void UiServeurTcp::on_pushButton_2_clicked()
    {

}



            void UiServeurTcp::onQTcpSocketreadyRead()
    {
            QByteArray data;
            QByteArray reponse;
            ui ->textEditMessages->append("dans readyRead");
            //reception du message client
            data =socKClient->readAll();
            ui ->textEditMessages->append(data);
            //réponse
            reponse ="msg recu :"+data;
            socKClient->write(reponse);
}
            void UiServeurTcp::onQTcpSocketdisconnected()
    {
            ui->textEditMessages->append("Disconnected");
           QTcpSocket *socketClient;
           socKClient=qobject_cast<QTcpSocket*>(sender());
            disconnect(socketClient,nullptr,this,nullptr);
            socketClient->deleteLater();
}
