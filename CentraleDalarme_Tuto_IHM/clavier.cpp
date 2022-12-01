#include "clavier.h"
#include "ui_clavier.h"

Clavier::Clavier(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Clavier)
{
    ui->setupUi(this);
    connect(ui->pushButton_0,&QPushButton::clicked,this,&Clavier::TraiterChiffre);
    connect(ui->pushButton_1,&QPushButton::clicked,this,&Clavier::TraiterChiffre);
}

Clavier::~Clavier()
{
    delete ui;
}


void Clavier::on_pushButton_Marche_clicked()
{
    QString texteBouton = ui->pushButton_Marche->text();
    QMessageBox messageMarche;
    messageMarche.setText("j'ai appuyé sur la touche " + texteBouton);
    messageMarche.exec();
}


void Clavier::on_pushButton_Marche_pressed()
{
    QString texteBouton = ui->pushButton_Marche->text();
    QMessageBox messageMarche;
    messageMarche.setText("la touché ennfoncé est   " + texteBouton);
    messageMarche.exec();
}


void Clavier::on_pushButton_Marche_released()
{
    QString texteBouton = ui->pushButton_Marche->text();
    QMessageBox messageMarche;
    messageMarche.setText("j'ai relaché  la touche " + texteBouton);
    messageMarche.exec();
}

void Clavier::TraiterChiffre()
{
    QPushButton *pbouton = static_cast<QPushButton *>(sender());
    QString texteBouton = pbouton ->text();
    QMessageBox messageChiffre;
    messageChiffre.setText("j'ai appuyé sur la touche " + texteBouton);
    messageChiffre.exec();
}

