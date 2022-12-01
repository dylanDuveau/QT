#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class client; }
QT_END_NAMESPACE

class client : public QMainWindow
{
    Q_OBJECT

public:
    client(QWidget *parent = nullptr);
    ~client();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_Envoyer_clicked();

    void onQTcpSocketConnect();

    void onQTcpSocketDisconnect();

    void onQTcpSocketReadyRead();

    void onQTcpSocketStateChanged(QAbstractSocket::SocketState socketState);

    void onQTcpSocketErrorOccurred(QAbstractSocket::SocketError socketError);

private:
    Ui::client *ui;
    QTcpSocket sockVersServeur;
};
#endif // CLIENT_H
