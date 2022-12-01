#ifndef UISERVEURTCP_H
#define UISERVEURTCP_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
QT_BEGIN_NAMESPACE
namespace Ui { class UIServeurTCP; }
QT_END_NAMESPACE

class UIServeurTCP : public QWidget
{
    Q_OBJECT

public:
    UIServeurTCP(QWidget *parent = nullptr);
    ~UIServeurTCP();

private slots:
    void on_pushButton_Quitter_clicked();

    void on_pushButton_Lancer_clicked();
    //slot gestion serveur
    void onQTcpServeracceptError(QAbstractSocket::SocketError socketError);
    void onQTcpServernewConnection();

    //slot gestion communication client
    void onQTcpSockethostFound();
    void onQTcpSocketconnected();
    void onQTcpSocketdisconnected();
    void onQTcpSocketbytesWritten(qint64 bytes);
    void onQTcpSocketreadyRead();
    void onQTcpSocketdestroyed(QObject *obj = nullptr);
    void onQTcpSocketchannelReadyRead(int channel);
    void onQTcpSocketchannelBytesWritten(int channel, qint64 bytes);
    void onQTcpSocketaboutToClose();
    void onQTcpSocketreadChannelFinished();
    void onQTcpSocketStateChanged(QAbstractSocket::SocketState socketState);
    void onQTcpSocketErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    Ui::UIServeurTCP *ui;
    QTcpServer sockServ;
    QList <QTcpSocket*> listSockClient;
};
#endif // UISERVEURTCP_H
