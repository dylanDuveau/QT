#include "auditclientwidget.h"
#include "ui_auditclientwidget.h"

AuditClientWidget::AuditClientWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AuditClientWidget)
{
    ui->setupUi(this);
    socketDeDialogueAvecServeur = new QTcSocket (this);
    connect(sockVersServeur,QTcpSocket::connected,this,::QMainWindow::QTcpSocketConnected);
    connect(sockVersServeur,QTcpSocket::disconnected,this,::MainWindow::QTcpSocketConnected);
    connect(sockVersServeur,QTcpSocket::readyRead,this,::MainWindow::QTcpSocketConnected);
}

AuditClientWidget::~AuditClientWidget()
{
    if(socketDeDialogueAvecServeur != nullptr)
    {
      socketDeDialogueAvecServeur->close();
      delete socketDeDialogueAvecServeur;
    }
    delete ui;
}


void AuditClientWidget::on_pushButtonConnexion_clicked()
{
    if(ui->pushButtonConnexion->text()=="conexion")
    {
        socketDeDialoguesAvecServeur->connectToHost (ui ->lineEditAdresseIP->text(),ui->lineEdiPort)
    }
}
void AuditClientWidget::onQTcpSocketDisconected()
{
       ui->textEditEtat->append("Deconnected");
       ui->lineEditAdresseIP->setEnabled(true);
       ui->lineEditPort->setEnabled(true);
       ui->pushButtonConnexion->setEnabled(true);
       ui->pushButtonQuitter->setEnabled(true);
}


void AuditClientWidget::on_pushButtonQuitter_clicked()
{

}


void AuditClientWidget::on_pushButtonOrdinateur_clicked()
{

}


void AuditClientWidget::on_pushButtonUtilisateur_clicked()
{

}


void AuditClientWidget::on_pushButtonArchitecture_clicked()
{

}


void AuditClientWidget::on_pushButtonOS_clicked()
{

}


void AuditClientWidget::onQTcpSocketAboutToClose()
{

}

void AuditClientWidget::onQTcpSocketBytesWritten(qint64 bytes)
{

}

void AuditClientWidget::onQTcpSockeChanneltBytesWritten(qint64 bytes)
{

}

