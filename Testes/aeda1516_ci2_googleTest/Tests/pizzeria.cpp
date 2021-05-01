/*
 * pizzeria.cpp
 *
 *  Created on: 25 Oct 2015
 *      Author: RRossetti
 */

#include "pizzeria.h"

/*
 * CLASS MENU
 */

Menu::Menu() {
	id = 0;
	name = "";
	likes = 0;
}

Menu::Menu(int id1, string n1, vector<string> is1, int lks1) {
	id = id1;
	name = n1;
	ingredients = is1;
	likes = lks1;
}

int Menu::getId() const { return id; }
void Menu::setId(int id1) { id = id1; }
string Menu::getName() const { return name; }
void Menu::setName(string n1) { name = n1; }
vector<string> Menu::getIngredients() const { return ingredients; }

Menu::Menu(string n1, vector<string> is1) {
    static int ids = 1;
    id = ids;
    likes = 0;
    ingredients = is1;
    name = n1;
    ids++;
}

void Menu::setIngredients(const vector<string> &is1) {
    if(isSet(is1))
    {
        ingredients=is1;
        return;
    }
    throw ExceptionIngredientsRepeated();
}

bool Menu::operator<(const Menu &menu2)
{
    if(likes == menu2.getLikes())
    {
        if(ingredients.size() == menu2.getIngredients().size())
            return name < menu2.getName();
        else
            return ingredients.size() < menu2.getIngredients().size();
    }
    else
        return likes > menu2.getLikes();
}

/*
 * CLASS CUSTOMER
 */

Customer::Customer(int nif1, string n1) {
	nif = nif1;
	name = n1;
}

int Customer::getNIF() const {
	return nif;
}

string Customer::getName() const {
	return name;
}


/*
 * CLASS PIZZERIA
 */

Pizzeria::Pizzeria() { }

Pizzeria::Pizzeria(vector<Menu> ms1) {
	menus = ms1;
}

vector<Menu> Pizzeria::getMenus() const { return menus; }

vector<Customer*> Pizzeria::getCustomers() const { return customers; }

int Pizzeria::addCustomer(Customer* c1) {
	customers.push_back(c1);
	return customers.size();
}

vector<Menu> Pizzeria::optionsWithinIngredientLimits(int i1, int i2) const {
    vector<Menu> aux;
    if(i1<1||i2<1||i2<i1)
        throw ExceptionInvalidIngredientLimits();
    for(size_t i=0;i<menus.size();i++)
    {
        if(menus.at(i).getIngredients().size()>=i1 && menus.at(i).getIngredients().size()<=i2)
            aux.push_back(menus.at(i));
    }
    return aux;
}

//vector<Menu> Pizzeria::optionsWithinIngredientLimits(int i1, int i2) const {
//    vector<Menu> result;
//    if(i1 < 1 || i2 < 1 || i2 < i1)
//        throw ExceptionInvalidIngredientLimits();
//    for(size_t i = 0; i < menus.size(); i++)
//    {
//        if((menus.at(i).getIngredients().size() >= i1) && (menus.at(i).getIngredients().size() <= i2))
//            result.push_back(menus.at(i));
//    }
//    return result;
//}

vector<Menu> Pizzeria::popularityRank() const {
    vector<Menu> result = menus;
    insertionSort(result);
    return result;
}

Customer *Pizzeria::chefCustomer() {
    double ratio, maxRatio;
    Customer *c1;
    int count, nLikes;
    for(size_t i=0; i<customers.size();i++) {
        count=0;
        nLikes=0;
        for (size_t j = 0; j < menus.size(); j++)
            if (customers.at(i)->getName() == menus.at(j).getName()) {
                count++;
                nLikes += menus.at(j).getLikes();

            }
        ratio=nLikes/count;
        if(i==0)
        {
            maxRatio=ratio;
            c1=customers.at(i);
        }
        else if(ratio>maxRatio)
        {
            maxRatio=ratio;
            c1=customers.at(i);
        }
    }
    return c1;
}

//Customer *Pizzeria::chefCustomer() {
//
//    int numMenus = 0;
//    int numLikes = 0;
//    int prevRatio;
//    int ratio;
//    Customer *creative = new Customer(0,"");
//    for(auto x = customers.begin(); x != customers.end(); x++)
//    {
//        numMenus = 0;
//        numLikes = 0;
//        for(size_t i = 0; i < menus.size(); i++) {
//            if (menus.at(i).getName() == (*x)->getName()) {
//                numLikes += menus.at(i).getLikes();
//                numMenus++;
//            }
//        }
//        ratio = numLikes/numMenus;
//        if(x == customers.begin()) {
//            prevRatio = ratio;
//            *creative = *(*x);
//        }
//        else
//        {
//            if(prevRatio < ratio) {
//                prevRatio = ratio;
//                *creative = *(*x);
//            }
//        }
//    }
//    return creative;
//}

Menu &Pizzeria::removeIngredient(vector<string> is1, string i1) {
    int count = 0;
    for(size_t i = 0; i < menus.size(); ++i)
    {
        int countV = 0;
        for(size_t j = 0; j < menus.at(i).getIngredients().size(); ++j)
        {
            for(size_t k = 0; k < is1.size(); ++k)
            {
                if(menus.at(i).getIngredients().at(j) == is1.at(k))
                {
                    countV++;
                    break;
                }
            }
        }
        if(countV == is1.size())
        {
            count++;
            int count2 = 0;
            count2 = 0;
            for(auto x = menus.at(i).getIngredients().begin(); x != menus.at(i).getIngredients().end(); ++x)
            {
                if((*x) == i1)
                {
                    count2++;
                    x = menus.at(i).getIngredients().erase(x);
                    return menus.at(i);
                }
            }
            if(count2 == 0)
                throw Menu::ExceptionIngredientNotPresent(i1);
        }
    }
    if(count == 0)
        throw ExceptionInexistentMenu();

}




