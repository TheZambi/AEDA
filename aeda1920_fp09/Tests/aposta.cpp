#include "aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

// a alterar
bool Aposta::contem(unsigned num) const
{
	return numeros.find(num)!=numeros.end();
}

//a alterar
void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
    int aux=0;
    for(auto iter=valores.begin();iter!=valores.end() && aux<n; iter++)
    {
        if(numeros.find(*iter) == numeros.end()) {
            numeros.insert(*iter);
            aux++;
        }
    }
}

//a alterar
unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
    int counter =0;
    for(auto iter=numeros.begin();iter!=numeros.end();iter++)
    {
        if(sorteio.find(*iter)!=sorteio.end())
            counter++;
    }
    return counter;
}





