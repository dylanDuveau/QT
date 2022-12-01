#ifndef AUDITSERVEURMULTI_H
#define AUDITSERVEURMULTI_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QProcess>
#include <QtNetwork>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class AuditServeurMulti; }
QT_END_NAMESPACE

class AuditServeurMulti : public QWidget
{
    Q_OBJECT

public:
    AuditServeurMulti(QWidget *parent = nullptr);
    ~AuditServeurMulti();
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
    Ui::AuditServeurMulti *ui;
    QTcpServer *socketEcouteServeur;
    QList<QTcpSocket *> listeSocketDialogueClient;
    QList<QProcess *> listeProcess;

};
#endif // AUDITSERVEURMULTI_H
