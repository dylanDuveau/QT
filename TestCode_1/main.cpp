#include<QtGlobal>
#include<iostream>
#include<QDebug>
#include"code.h"



using namespace std;
#define TAILLE_CODE 4

int main(int argc, char *argv[])
{
   char choix;
   quint8 combinaison[TAILLE_CODE];
   Code lecode;

   cout <<"voulez cous modifier le code ? O/N :";
   cin >> choix;
   if(choix =='O' || choix =='o')
   {
       cout << "Entrez votre code à 4 chiffres :";
       for(int indice =0 ; indice < TAILLE_CODE ; indice++)
       {
           cin >> combinaison[indice];
           combinaison[indice] -= '0';
       }
        // qDebug() << combinaison(0) << combinaison(1) << combinaison(2) << combinaison(3);
       lecode.Memoriser(combinaison);
   }
   cout <<"Veuillez saisir un code :" << endl;
   cout <<"Entrez le code à 4 chiffre :";
   for(int indice =0 ; indice < TAILLE_CODE ; indice++){
      cin >> combinaison[indice];
      combinaison[indice] -= '0';
   }
   if(lecode.verifierCode(combinaison))
       cout << "Le code est valide" << endl <<endl;
   else
         cout << "Le code est invalide" << endl <<endl;
   return 0;
}
