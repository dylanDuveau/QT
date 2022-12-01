#include <iostream>
#include <QtGlobal>
#include "code.h"

using namespace std;

#define TAILLE_CODE 4

int main(int argc, char *argv[])
{
    char choix;
    quint8 combinaison[TAILLE_CODE];
    Code lecode;

    cout << "Voulez-vous modifier le code O/N : ";
    cin >> choix;
    if(choix == 'O' || choix =='o')
    {
        cout << "Entrez le code à 4 chiffres : ";
        for(int i=0 ; i < TAILLE_CODE ; i++)
        {
            cin >> combinaison[i] ;
            combinaison[i] -= '0';
        }
        lecode.MemoriserCode(combinaison);
    }
    cout << "Veuillez saisir un code : " << endl;
    cout << "Entrez le code à 4 chiffres : ";
    for(int i=0 ; i < TAILLE_CODE ; i++)
    {
        cin >> combinaison[i] ;
        combinaison[i] -= '0';
    }
    if(lecode.VerifierCode(combinaison))
        cout << "Le code est valide " << endl;
    else
        cout << "Le code est invalide " << endl;
    return 0;
}
