/*
 * jogo.cpp
 */

#include "jogo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;


unsigned int Jogo::numPalavras(string frase)
{
  if ( frase.length() == 0 ) return 0;

  unsigned n=1;
  size_t pos = frase.find(' ');
  while (pos != string::npos) {
    frase = frase.substr(pos+1);
    pos = frase.find(' ');
    n++;
  }
  return n;
}

// a implementar
Jogo::Jogo()
{
    criancas={};
}

// a implementar
Jogo::Jogo(list<Crianca>& lc2)
{
    criancas = lc2;
}

// a implementar
void Jogo::insereCrianca(const Crianca &c1)
{
    criancas.push_back(c1);
}

// a implementar
list<Crianca> Jogo::getCriancasJogo() const
{
    list<Crianca> res;
    for(auto i = criancas.begin(); i != criancas.end() ; ++i)
        res.push_back(*i);
    return res;
}

// a implementar
string Jogo::escreve() const
{
    string res;
    for(auto i = criancas.begin(); i != criancas.end() ; ++i)
        res += i->escreve()+"\n";

    return res;
}

// a implementar
Crianca& Jogo::perdeJogo(string frase)
{
    Crianca *c1 = new Crianca();
    int nPalavras = this->numPalavras(frase)%criancas.size();
    auto iter=criancas.begin();
    int counter = 0;
    for(auto iter=criancas.begin();iter!=criancas.end();++iter)
    {
        if(counter==nPalavras)
            *c1=*iter;

    counter++;
    }
    return *c1;
}

// a implementar
list<Crianca>& Jogo::inverte()
{
    criancas.reverse();
    return criancas;
}

// a implementar
list<Crianca> Jogo::divide(unsigned id)
{
    list<Crianca> res;
    for(list<Crianca>::iterator iter = criancas.begin(); iter != criancas.end(); iter++)
    {
        if(iter->getIdade()>id)
        {
            res.push_back(*iter);
            iter =  criancas.erase(iter);
            iter--;
        }
    }
    return res;
}

// a implementar
void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
    for(auto i = l1.begin(); i != l1.end() ; ++i)
        criancas.push_back(*i);
}

// a implementar
bool Jogo::operator==(Jogo& j2)
{
	return criancas==j2.getCriancasJogo();
}

// a implementar
list<Crianca> Jogo::baralha() const
{
    list<Crianca> res;
    for(auto iter=criancas.begin(); iter != criancas.end(); iter++)
        if(rand()%2==0)
            res.push_back(*iter);
        else
            res.push_front(*iter);

    return res;
}
