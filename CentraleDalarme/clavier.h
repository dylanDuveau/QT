#ifndef CLAVIER_H
#define CLAVIER_H

#include <QWidget>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Clavier; }
QT_END_NAMESPACE

class Clavier : public QWidget
{
    Q_OBJECT

public:
    Clavier(QWidget *parent = nullptr);
    ~Clavier();

private slots:
    void on_pushButton_Marche_clicked();

    void on_pushButton_Marche_pressed();

    void on_pushButton_Marche_released();
    void TraiterChiffre();

private:
    Ui::Clavier *ui;
    QTimer timerLed;
};
#endif // CLAVIER_H
