#ifndef AUDITSERVEURMONO_H
#define AUDITSERVEURMONO_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QProcess>
#include <QtNetwork>

QT_BEGIN_NAMESPACE
namespace Ui { class AuditServeurMono; }
QT_END_NAMESPACE

class AuditServeurMono : public QWidget
{
    Q_OBJECT

public:
    AuditServeurMono(QWidget *parent = nullptr);
    ~AuditServeurMono();

private slots:
    void on_pushButton_Lancer_clicked();
    void on_pushButton_Quitter_clicked();

    //slot gestion communication client
       void onQTcpServeracceptError(QAbstractSocket::SocketError socketError);
       void onQTcpServernewConnection();
       void onQTcpSockethostFound();
       void onQTcpSocketconnected();
       void onQTcpSocketdisconnected();
       void onQTcpSocketbytesWritten(qint64 bytes);
       void onQTcpSocketreadyRead();
       void onQTcpSocketaboutToClose();
       void onQTcpSocketStateChanged(QAbstractSocket::SocketState socketState);
       void onQTcpSocketErrorOccurred(QAbstractSocket::SocketError socketError);

       void onQProcess_readyReadStandardOutput();


private:
    Ui::AuditServeurMono *ui;
    QTcpServer *socketEcouteServeur;
    QTcpSocket *socketDialogueClient;
    QProcess *process;
};
#endif // AUDITSERVEURMONO_H
