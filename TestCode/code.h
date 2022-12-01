#ifndef CODE_H
#define CODE_H

#include <QtGlobal>

class Code
{
private:
    quint8 *codeUsine;
    quint8 *codeUtilisateur;

public:
    const int tailleCode;
    Code(const int _tailleCode=4);
    bool VerifierCode(const quint8 _unCode[]);
    void MemoriserCode(const quint8 _unCode[]);
};

#endif // CODE_H
