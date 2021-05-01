
#include "animal.h"
#include <sstream>
using namespace std;

/*
 * Classe Animal
 */

int  Animal::maisJovem=0;

Voador::Voador(int vmax, int amax)
{
    this->velocidade_max=vmax;
    this->altura_max=amax;
}

Morcego::Morcego(string nome, int idade, int vmax, int amax):Animal(nome, idade),Voador(vmax,amax)
{}

Animal::Animal(string nome, int idade)
{
    this->nome=nome;
    this->idade=idade;
    if(!getMaisJovem())
        Animal::maisJovem=idade;
    if(idade<getMaisJovem())
        Animal::maisJovem=idade;
}

Cao::Cao(string nome, int idade, string raca):Animal(nome,idade)
{
    this->raca=raca;
}

string Animal::getNome() const {
	return nome;
}

int Animal::getMaisJovem()
{return Animal::maisJovem;}

bool Cao::eJovem() const
{
    if(idade<5)
        return true;
    return false;
}

bool Morcego::eJovem() const
{
    if(idade<4)
        return true;
    return false;
}

void Animal::designateVet(Veterinario &vet) {this->vet=&vet;hasVet=true;}

string Cao::getInformacao() const
{
    string info;
    if(hasVet)
        info = ", " + vet->getNome() + ", " + to_string(vet->getCodOrdem());
    return nome + ", " + to_string(idade)  + info+ ", " + raca;
}

string Morcego::getInformacao() const {
    return nome + ", " + to_string(idade) + ", " + to_string(velocidade_max) +  ", " + to_string(altura_max);
}


