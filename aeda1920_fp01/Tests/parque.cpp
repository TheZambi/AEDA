#include "parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli) :numMaximoClientes(nMaxCli),lotacao(lot)
{
    vagas=lot;
    clientes={};
}

unsigned int ParqueEstacionamento::getNumLugares() const
{
    return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const
{
    return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const
{
    for(int i=0; i< clientes.size(); i++)
    {
        if(nome==clientes.at(i).nome)
            return i;
    }
    return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
    if(vagas>0 && numMaximoClientes > clientes.size())
    {
        InfoCartao info;
        info.nome=nome;
        info.presente=false;
        clientes.push_back(info);
        return true;
    }
    return false;

}

bool ParqueEstacionamento::entrar(const string & nome)
{
    int pos=posicaoCliente(nome);
    if(pos > -1)
    {
        if (clientes.at(pos).presente == false and (vagas > 0)) {
            clientes.at(pos).presente = true;
            vagas -= 1;
            return true;
        }
    }
    return false;
}

bool ParqueEstacionamento::retiraCliente(const string & nome)
{
    int pos=posicaoCliente(nome);
    if(pos!=-1)
    {
        if(clientes.at(pos).presente==false)
        {
            clientes.erase(clientes.begin()+pos);
            return true;
        }
    }
    return false;
}

bool ParqueEstacionamento::sair(const string & nome)
{
    int pos=posicaoCliente(nome);
    if(pos!=-1 and clientes.at(pos).presente==true)
    {
        vagas++;
        clientes.at(pos).presente=false;
        return true;
    }
    return false;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
    return lotacao-vagas;
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const
{
    return clientes.size();
}