#ifndef UISERVEURTCP_H
#define UISERVEURTCP_H

#include <QMainWindow>
#include<QTcpServer>
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class UiServeurTcp; }
QT_END_NAMESPACE

class UiServeurTcp : public QMainWindow
{
    Q_OBJECT

public:
    UiServeurTcp(QWidget *parent = nullptr);
    ~UiServeurTcp();

private slots:
    void on_pushButtonLancer_clicked();
    void on_pushButtonQ_clicked();

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
    Ui::UiServeurTcp *ui;
    QTcpServer sockserv;
    QTcpSocket *socKClient;
};
#endif // UISERVEURTCP_H
