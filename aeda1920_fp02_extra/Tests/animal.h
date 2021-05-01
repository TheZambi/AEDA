
#ifndef SRC_ANIMAL_H_
#define SRC_ANIMAL_H_

#include "veterinario.h"
#include <string>
using namespace std;


class Animal {
protected:
	string nome;
	int idade;
	Veterinario *vet;
	static int maisJovem;
	bool hasVet=false;
public:
	Animal(string nome, int idade);
	virtual ~Animal(){};
	string getNome() const;
    static int getMaisJovem();

	//completar
    virtual bool eJovem()const = 0;
    virtual string getInformacao() const=0;
    void designateVet(Veterinario &vet);
    string getVetName(){return vet->getNome();}
    int getIdade(){return idade;}
};


class Cao: public Animal {
	string raca;
public:
	Cao(string nome, int idade, string raca);
	//completar
    bool eJovem()const;
    string getInformacao() const;
};


class Voador {
protected:
	int velocidade_max;
	int altura_max;
public:
	Voador(int vmax, int amax);
    virtual ~Voador(){};
	//completar
    virtual string getInformacao() const=0;
};


class Morcego: public Animal, public Voador {
public:
	Morcego(string nome, int idade, int vmax, int amax);
	//completar
    bool eJovem()const;
    string getInformacao() const;

};


#endif /* SRC_ANIMAL_H_ */
