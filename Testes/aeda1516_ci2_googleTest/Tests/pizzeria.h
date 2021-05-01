/*
 * pizzaria.h
 *
 *  Created on: Oct 21, 2015
 *      Author: RRossetti
 */

#ifndef PIZZERIA_H_
#define PIZZERIA_H_

#include <string>
#include <vector>
#include <iostream>

#include "sequentialSearch.h"
#include "insertionSort.h"

using namespace std;

class Menu {
	int id;
	string name;
	int likes;
	vector<string> ingredients;
public:
	Menu();
	Menu(string n1, vector<string> is1);
	Menu(int id1, string n1, vector<string> is1, int lks1);
	int getId() const;
	void setId(int id1);
	string getName() const;
	void setName(string n1);
	vector<string> getIngredients() const;
	void addLike() { ++likes; }
	int getLikes() const { return likes; }

	class ExceptionIngredientsRepeated {};
	class ExceptionIngredientNotPresent
    {
	    string ingredient;
    public:
        ExceptionIngredientNotPresent(string ingredient) {this->ingredient = ingredient;};
        string getIngredient() {return ingredient;};
    };

	void setIngredients(const vector<string> &is1);

	bool operator<(const Menu &menu2);
};

class Customer {
	int nif;
	string name;
public:
	Customer(int nif1, string n1);
	int getNIF() const;
	string getName() const;
};

class Pizzeria {
	vector<Menu> menus;
	vector<Customer*> customers;
public:
	Pizzeria();
	Pizzeria(vector<Menu> ms1);
	vector<Menu> getMenus() const;
	vector<Customer*> getCustomers() const;
	int addCustomer(Customer* c1);

	vector<Menu> optionsWithinIngredientLimits(int i1, int i2) const;
	vector<Menu> popularityRank() const;
	Customer* chefCustomer();
	Menu& removeIngredient(vector<string> is1, string i1);
    class ExceptionInexistentMenu {};

	class ExceptionInvalidIngredientLimits {};

};

template <class Comparable>
bool isSet(const vector<Comparable>& v1)
{
    vector<Comparable> aux;

    for(size_t i=0; i<v1.size();i++) {
       for(size_t j=0;j<aux.size();j++)
           if(aux.at(j)==v1.at(i))
                return false;
        aux.push_back(v1.at(i));
    }
    return true;
}


#endif /* PIZZERIA_H_ */
