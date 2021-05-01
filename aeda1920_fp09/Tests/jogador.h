#ifndef JOGADOR_H_
#define JOGADOR_H_

#include "aposta.h"
#include <string>

using namespace std;

//a alterar
struct apostaHash
{
	int operator() (const Aposta & ap) const
	{
	    int sum=0;
	    for(auto iter=ap.getNumeros().begin();iter!=ap.getNumeros().end();iter++)
	        sum+=*iter;
		return sum;
	}
	
	bool operator() (const Aposta & ap1, const Aposta & ap2) const
	{
	    if(ap1.getNumeros().size()!=ap2.getNumeros().size())return false;
	    if(ap1.calculaCertos(ap2.getNumeros())==ap1.getNumeros().size())
	        return true;
	    return false;
	}
};



typedef unordered_set<Aposta, apostaHash, apostaHash> tabHAposta;

class Jogador
{
	tabHAposta apostas;
	string nome;
public:
	Jogador(string nm="anonimo") { nome=nm; }
	void adicionaAposta(const Aposta & ap);
	unsigned apostasNoNumero(unsigned num) const;
	tabHAposta apostasPremiadas(const tabHInt & sorteio) const;
	unsigned getNumApostas() const { return apostas.size(); }
};

#endif /*JOGADOR1_H_*/
