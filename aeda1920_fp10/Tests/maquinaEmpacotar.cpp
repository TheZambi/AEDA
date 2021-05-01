#include "maquinaEmpacotar.h"
#include <sstream>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


// a alterar
unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
    unsigned int counter=0;
    for(size_t i=0;i<objs.size();i++)
    {
        if(objs.at(i).getPeso()<=capacidadeCaixas)
        {
            objetos.push(objs.at(i));
            objs.erase(objs.begin()+i);
            i--;
            counter++;
        }
    }
	return counter;
}

// a alterar
Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
    HEAP_CAIXAS aux;
	Caixa cx;
    while(!caixas.empty())
    {
        if(caixas.top().getCargaLivre()>=obj.getPeso()) {
            cx = caixas.top();
            caixas.pop();
            break;
        }
        else
        {
            aux.push(caixas.top());
            caixas.pop();
        }
    }
    while(!aux.empty())
    {
        caixas.push(aux.top());
        aux.pop();
    }
	return cx;
}

// a alterar
unsigned MaquinaEmpacotar::empacotaObjetos() {
    while(!this->objetos.empty())
    {
        Caixa cx = procuraCaixa(const_cast<Objeto &>(objetos.top()));
        cx.addObjeto(const_cast<Objeto &>(objetos.top()));
        this->caixas.push(cx);
        objetos.pop();
    }
	return caixas.size();
}

// a alterar
string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
    if(objetos.size()==0)
        return "Nao ha objetos!\n";
    string ss="";
    HEAP_OBJS copy=objetos;
    while(!copy.empty())
    {
        ss += "O" + to_string(copy.top().getID()) + ": " + to_string(copy.top().getPeso()) + "\n";
        copy.pop();
    }
	return ss;
}

// a alterar
Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	Caixa cx;
	if(this->caixas.size()==0)
	    throw MaquinaSemCaixas();
	HEAP_CAIXAS copy=caixas;
	cx=copy.top();
	copy.pop();
	while(!copy.empty())
    {
	    if(copy.top().getSize()>cx.getSize())
	        cx=copy.top();
	    copy.pop();
    }
	return cx;
}



