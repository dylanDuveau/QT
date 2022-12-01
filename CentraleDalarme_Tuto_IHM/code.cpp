#include "code.h"


Code::Code( const int  _tailleCode):
    tailleCode(_tailleCode)
{
     codeUsine = new quint8[tailleCode];
      codeUtilisateur = new quint8[tailleCode];

    for(int indice = 0; indice < tailleCode;indice++){
        codeUsine[indice] = indice+1;
        codeUtilisateur[indice] = 0;
    }
}


Code::~Code()
{
    delete codeUsine;
    delete codeUtilisateur;
}

bool Code::verifierCode(const quint8 _unCode[])
{
    bool codeOK = true;
    for(int indice = 0 ; indice < tailleCode && codeOK == true; indice++)
    {
        if(_unCode[indice] != codeUtilisateur[indice] && _unCode[indice] !=codeUsine[indice])
            codeOK = false;
    }
    return codeOK;
}
void Code::Memoriser(const quint8 _uncode[])
{
for (int indice = 0 ; indice < tailleCode ; indice++)
    codeUtilisateur[indice] = _uncode[indice];


}

