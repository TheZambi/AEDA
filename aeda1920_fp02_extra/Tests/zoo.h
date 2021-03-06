#ifndef ZOO_H_
#define ZOO_H_

#include "animal.h"
#include <vector>


class Zoo {
	vector<Animal *> animais;
	vector<Veterinario *> veterinarios;
public:
	int numAnimais() const;
	int numVeterinarios() const;
	//completar
    void adicionaAnimal(Animal *a1);
    string getInformacao() const;
    bool animalJovem(string nomeA);
    bool removeVeterinario (string nomeV);
    bool operator < (Zoo& zoo2) const;
    void alocaVeterinarios(istream &isV);
};


#endif /* ZOO_H_ */
