#ifndef CODE_H
#define CODE_H
#include <QtGlobal>

class Code
{
public:

    Code(int _tailleCode=4);
    ~Code();
bool verifierCode(const quint8 _unCode[]);
void Memoriser(const quint8 _uncode[]);

private:
    int tailleCode;
    quint8  *codeUsine;
    quint8 *codeUtilisateur;
};

#endif // CODE_H
