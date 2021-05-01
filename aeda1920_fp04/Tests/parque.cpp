#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <algorithm>
#include <vector>

using namespace std;



ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
	lotacao(lot), numMaximoClientes(nMaxCli) {
    numClientes = 0;
    vagas=lot; 
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }

unsigned int ParqueEstacionamento::getNumLugares() const { return lotacao; }

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const { return lotacao-vagas; }


// a imnplementar
int ParqueEstacionamento::posicaoCliente(const string &nome) const
{
    for (int i=0; i<this->clientes.size(); ++i )
        if(this->clientes.at(i).nome==nome)
            return i;
    return -1;
}

//a implementar
int ParqueEstacionamento::getFrequencia(const string &nome) const
{
    int pos = posicaoCliente(nome);
    if(pos==-1)
        throw ClienteNaoExistente(nome);
    return clientes.at(pos).frequencia;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
 	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
    info.presente = false;
	clientes.push_back(info);
	numClientes++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	vagas--;
	clientes.at(pos).frequencia++;
	return true;
}

// a alterar/atualizar ?
bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}

		
// a implementar
void ParqueEstacionamento::ordenaClientesPorFrequencia()
{
    insertionSort( clientes);
}


// a implementar
void ParqueEstacionamento::ordenaClientesPorNome()
{
    vector<InfoCartao> ordenado;
    bool notFound=true;
    if(clientes.size()>0)
        ordenado.push_back(clientes.at(0));
    for(size_t i=1;i<clientes.size();++i)
    {
        for (size_t j = 0; j < ordenado.size(); ++j)
            if (clientes.at(i).nome < ordenado.at(j).nome) {
                ordenado.insert(ordenado.begin() + j, clientes.at(i));
                notFound=false;
                break;
            }
        if(notFound)
            ordenado.insert(ordenado.end(),clientes.at(i));
        notFound=true;
    }
    clientes=ordenado;

}

// a implementar
vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2)
{
    this->ordenaClientesPorFrequencia();
    vector<string> nomes;
    for(size_t i=0; i<clientes.size(); ++i)
        if(clientes.at(i).frequencia<=n2 && clientes.at(i).frequencia>=n1)
            nomes.push_back(clientes.at(i).nome);
    return nomes;
}


// a implementar
ostream & operator<<(ostream & os, const ParqueEstacionamento & pe)
{
    return os;
}


// a implmentar
InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const
{
    InfoCartao info;
    return info;
}

bool operator<(InfoCartao left, InfoCartao right)
{
    if(left.frequencia == right.frequencia)
        return (left.nome<right.nome);
    else
        return left.frequencia > right.frequencia;
}
