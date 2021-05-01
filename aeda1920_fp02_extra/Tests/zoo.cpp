#include "zoo.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

/*
 * Classe Zoo
 */

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1)
{
    animais.push_back(a1);
}

string Zoo::getInformacao() const
{
    string info="";
    for(size_t i=0;i<animais.size();i++)
        info += animais.at(i)->getInformacao();
    return info;
}
bool Zoo::animalJovem(string nomeA)
{
    for(size_t i=0;i<animais.size();i++)
        if(animais.at(i)->getNome()==nomeA)
            return animais.at(i)->eJovem();
        return false;
}

void Zoo::alocaVeterinarios(istream &isV)
{
    string aux, nome;
    long cod;int counter=0;
    while(getline(isV,aux))
    {
        if(counter){
            cod=stol(aux);
            veterinarios.push_back(new Veterinario(nome,cod));
            counter=-1;
        }
        else
            nome=aux;
        counter++;
    }
    for(size_t i=0; i<animais.size();i++)
        animais.at(i)->designateVet(*veterinarios.at(i%3));
}

bool Zoo::removeVeterinario (string nomeV)
{
    for(size_t i=0; i<veterinarios.size();i++)
        if(nomeV==veterinarios.at(i)->getNome())
        {
            for(size_t j=0;j<animais.size();j++)
                if(animais.at(j)->getVetName()==nomeV)
                    if(i==veterinarios.size()-1)
                        animais.at(i)->designateVet(*veterinarios.at(0));
                    else
                        animais.at(i)->designateVet(*veterinarios.at(i+1));
            veterinarios.erase(veterinarios.begin()+i);
            return true;
        }
    return false;
}

bool Zoo::operator < (Zoo& zoo2) const
{
    int totalIdades1=0, totalIdades2=0;
    for(size_t i=0; i<this->animais.size();i++)
        totalIdades1+=animais.at(i)->getIdade();
    for(size_t i=0; i<zoo2.animais.size();i++)
        totalIdades2+=zoo2.animais.at(i)->getIdade();
    return totalIdades1<totalIdades2;
}