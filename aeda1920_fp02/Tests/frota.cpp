#include "frota.h"
#include <string>

using namespace std;

void Frota::adicionaVeiculo(Veiculo *v1)
{
    veiculos.push_back(v1);
}

int Frota::numVeiculos() const
{
    return veiculos.size();
}

int Frota::menorAno() const
{
    if(veiculos.size()==0)
        return 0;
    int menorAno=veiculos.at(0)->getAno();
    for(size_t i=1; i<veiculos.size(); ++i)
    {
        if(veiculos.at(i)->getAno()<menorAno)
            menorAno=veiculos.at(i)->getAno();
    }
    return menorAno;
}

ostream& operator<<(ostream & o, const Frota & f)
{
    for(size_t i=0; i<f.veiculos.size(); ++i)
        f.veiculos.at(i)->info();
    return o;
}

vector<Veiculo *> Frota::operator () (int anoM) const
{
    vector<Veiculo *> aux;
    for(size_t i=0; i<veiculos.size(); ++i)
    {
        if(veiculos.at(i)->getAno()==anoM)
            aux.push_back(veiculos.at(i));
    }
    return aux;
}

float Frota::totalImposto() const
{
    float total=0;
    for(size_t i=0; i<veiculos.size(); ++i)
        total += veiculos.at(i)->calcImposto();
    return total;
}