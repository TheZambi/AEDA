#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N> 
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }

template <class N>
class ArestaRepetida
{
public:
    N noInicio;
    N noDestino;
    ArestaRepetida(N inicio, N fim) { noDestino=fim;noInicio=inicio; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &aresta)
{ out << "Aresta repetida: "<< aresta.noInicio << " , " << aresta.noDestino; return out; }

template<class N>
class ArestaInexistente
{
public:
    N inicio,fim;
    ArestaInexistente(N ini, N f){inicio=ini;fim=f;}
};

template<class N>
std::ostream & operator<<(std::ostream &out, const ArestaInexistente<N> &ni)
{ out << "Aresta inexistente: " << ni.inicio << " , " << ni.fim; return out; }

// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

template<class N, class A>
Grafo<N, A>::Grafo()
{
    nos={};
}

template<class N, class A>
Grafo<N, A>::~Grafo()
{
    nos.clear();
}

template<class N, class A>
int Grafo<N, A>::numNos(void) const
{
    return nos.size();
}

template<class N, class A>
int Grafo<N, A>::numArestas(void) const
{
    int contador=0;
    for(int i=0;i<nos.size();++i)
        contador += nos.at(i)->arestas.size();
    return contador;
}

template<class N, class A>
Grafo<N, A> &Grafo<N, A>::inserirNo(const N &dados)
{

    for(int i=0; i<nos.size(); ++i) {
        if (nos.at(i)->info == dados) {
            NoRepetido<N> noRep(dados);
            throw noRep;
        }
    }
    No<N, A> *ptrNo = new No<N, A>(dados);
    nos.push_back(ptrNo);
    return *this;
}

template<class N, class A>
Grafo<N, A> &Grafo<N, A>::inserirAresta(const N &inicio, const N &fim, const A &val)
{
    size_t posNo;
    bool checkInicio=true, checkFim=false;
    for(size_t i=0; i<nos.size(); ++i)
    {
        if(nos.at(i)->info==inicio)
        {
            posNo=i;
            checkInicio = false;
        }
        if(nos.at(i)->info==fim)
            checkFim=false;
    }
    if(checkInicio)
        throw NoInexistente<N>(inicio);
    if(checkFim)
        throw NoInexistente<N>(fim);
    for(size_t i=0; i<nos.at(posNo)->arestas.size(); ++i)
    {
        if(nos.at(posNo)->arestas.at(i).destino->info==fim)
            throw ArestaRepetida<N>(inicio,fim);
    }
    No<N, A> *ptrNo = new No<N, A>(fim);
    Aresta<N,A> toAdd(ptrNo,val);
    nos.at(posNo)->arestas.push_back(toAdd);
    return *this;
}

template<class N, class A>
A & Grafo<N,A>::valorAresta(const N &inicio, const N &fim)
{
    bool no_existe=false;
    for(size_t i=0; i<numNos();i++)
        if(nos.at(i)->info==inicio) {
            no_existe=true;
            for (int i2 = 0; i2 < nos[i]->arestas.size(); i2++) {
                if (nos[i]->arestas[i2].destino->info == fim)
                    return nos[i]->arestas[i2].valor;
            }
        }
    if(!no_existe)
        throw NoInexistente<N>(inicio);
    throw ArestaInexistente<N>(inicio, fim);
}
