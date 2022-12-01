#include "Code.h"




bool Sode::VerifierCode(const quint8 unCode[])
{
    bool test=true;

    for (int i = 0; i < tailleCode && test == true; i++)
    {
        if (unCode[i]!=codeUtilisateur[i] && unCode[i]!=codeUsine[i])
            test = false;
    }
    return test;
}

void Sode::Memoriser(const quint8 nouveauCode[])
{
    for (int i = 0; i < tailleCode; i++)
        codeUtilisateur[i] = nouveauCode[i];
}



Sode::Sode(const int _tailleCode),
tailleCode(_tailleCode)
{

}
