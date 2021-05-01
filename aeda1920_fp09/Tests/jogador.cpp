#include "jogador.h"

//a alterar
void Jogador::adicionaAposta(const Aposta & ap)
{
    apostas.insert(ap);
}

//a alterar
unsigned Jogador::apostasNoNumero(unsigned num) const
{
    int total=0;
    for(auto itAp=apostas.begin();itAp!=apostas.end();itAp++)
    {
        for(auto itNum=itAp->getNumeros().begin();itNum!=itAp->getNumeros().end();itNum++)
        {
            if(*itNum==num)
                {
                total++;
                break;
                }
        }
//        if(itAp->contem(num)) total++;
    }
	return total;
}

//a alterar
tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
	tabHAposta money;
    for(auto itAp=apostas.begin();itAp!=apostas.end();itAp++) {
        if(itAp->calculaCertos(sorteio)>3)
            money.insert(*itAp);
    }

	return money;
}
