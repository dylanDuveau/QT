#ifndef AUDITCLIENT_H
#define AUDITCLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class AuditClient; }
QT_END_NAMESPACE

class AuditClient : public QWidget
{
    Q_OBJECT

public:
    AuditClient(QWidget *parent = nullptr);
    ~AuditClient();

private slots:
    void on_pushButtonQuitter_clicked();
    void on_pushButtonConnexion_clicked();
    void on_pushButtonArchitecture_clicked();
    void on_pushButtonOs_clicked();
    void on_pushButtonUtilisateur_clicked();
    void on_pushButtonOrdinateur_clicked();
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
    Ui::AuditClient *ui;
    QTcpSocket *socketDeDiaglogueAvecServeur;
    QString typeDeDemande;
};
#endif // AUDITCLIENT_H
