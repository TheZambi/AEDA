#include <queue>
#include <cstdlib>
#include "balcao.h"
#include "exceptions.h"

using namespace std;

//a alterar
Cliente::Cliente() {
    numPresentes=rand()%5+1;
}

//a alterar
int Cliente::getNumPresentes() const {
    return numPresentes;
}

//a alterar
Balcao::Balcao(int te): tempo_embrulho(te) {
    tempo_atual=0;
    prox_chegada=rand()%20;
    prox_saida=0;
    clientes_atendidos=0;
}

//a alterar
void Balcao:: proximoEvento()
{
}

//a alterar
void Balcao::chegada()
{
    cout << "tempo= " << tempo_atual<< endl;
    Cliente c1;
    if (clientes.empty()) prox_saida=tempo_atual+c1.getNumPresentes()*tempo_embrulho;
    clientes.push(c1);
    cout << "chegou novo cliente com " << c1.getNumPresentes() << " presentes" << endl;
    prox_chegada=tempo_atual+(rand()%20)+1;

}

//a alterar
void Balcao::saida()
{
    cout << "tempo= " << tempo_atual<< endl;
    Cliente c1;
    try {
        c1 = getProxCliente();
    }
    catch (FilaVazia &e) {
        cout << e.getMsg() << endl;
        return;
    }
    clientes.pop();
    cout << "cliente atendido: " << c1.getNumPresentes() << " presentes" << endl;
    clientes_atendidos++;
    if (clientes.empty()!=false)
        prox_saida=tempo_atual+clientes.front().getNumPresentes()*tempo_embrulho;
}


int Balcao::getTempoAtual() const { return tempo_atual; }

int Balcao::getProxChegada() const { return prox_chegada; }

//a alterar
ostream & operator << (ostream & out, const Balcao & b1)
{
     return out;
}

//a alterar
int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}

//a alterar
int Balcao::getProxSaida() const {
	return  prox_saida;
}

//a alterar
int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}

//a alterar
Cliente & Balcao::getProxCliente() {
    Cliente *c = new Cliente();
    if(clientes.size()==0)
        throw FilaVazia();
    c=&clientes.front();
    clientes.pop();
    return *c;
}

      
