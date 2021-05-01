#include <iostream>
#include <string>
#include <fstream>
#include "dicionario.h"
#include "bst.h"

using namespace std;

BST<PalavraSignificado> Dicionario::getPalavras() const {
	return palavras;
}

//a alterar
bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const {
     return this->palavra < ps1.palavra;
}

//a alterar
void Dicionario::lerDicionario(ifstream &fich)
{
    int count=0;
    string obj, aux;
    while(getline(fich, aux))
    {
        if(count==0)
            obj=aux;
        else {
            palavras.insert(PalavraSignificado(obj, aux));
            count=-1;
        }
        count++;
    }
}

//a alterar
string Dicionario::consulta(string palavra) const
{
    BSTItrIn<PalavraSignificado> it(palavras);
    bool maiorIsFound=true;
    PalavraSignificado *antes= new PalavraSignificado("",""), *dps=new PalavraSignificado("","");
    while(!it.isAtEnd())
    {
        if(it.retrieve().getPalavra()==palavra)
            return it.retrieve().getSignificado();
        if(it.retrieve().getPalavra()<palavra)
        {
            *antes=it.retrieve();
        }
        else if(it.retrieve().getPalavra()>palavra && maiorIsFound)
        {
            *dps=it.retrieve();
            maiorIsFound=false;
            break;
        }
        it.advance();
    }

    throw PalavraNaoExiste(antes,dps);
}

//a alterar
bool Dicionario::corrige(string palavra, string significado)
{
    BSTItrIn<PalavraSignificado> it(palavras);
    PalavraSignificado ola(palavra,significado);
    while(!it.isAtEnd())
    {
        if(it.retrieve().getPalavra()==palavra) {
            palavras.remove(it.retrieve());
            palavras.insert(ola);
            return true;
        }
        if(it.retrieve().getPalavra()>palavra)
        {
            break;
        }
        it.advance();
    }

    palavras.insert(ola);
    return false;

}

//a alterar
void Dicionario::imprime() const
{
    BSTItrIn<PalavraSignificado> it(palavras);
    while(!it.isAtEnd())
    {
        cout << it.retrieve().getPalavra() << endl;
        cout << it.retrieve().getSignificado() << endl;
        it.advance();
    }
    return;
}

