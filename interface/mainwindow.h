#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTcpSocket>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonConnexion_clicked();
    void on_pushButtonEnvoyer_clicked();
    void QTcpSocketEnvoyer();
    void QTcpSocketConnected();

private:
    Ui::MainWindow *ui;
    QTcpSocket sockVersServeur;

};
#endif // MAINWINDOW_H
