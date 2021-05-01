/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	// TODO
	Article *bought=new Article(client,barCode);
	bought->setPresent(present);
	bought->setDeliverHome(deliverHome);

	return bought;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {

	// TODO
	if(bags.back().size()<BAG_SIZE)
    {
	    bags.back().push(article);
        return;
    }
    stack<Article *> newStack;
    newStack.push(article);
    bags.push_back(newStack);

}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
	// TODO
	vector<Article*> presents;
	stack<Article*> aux;
	for(auto iter=bags.begin();iter!=bags.end();iter++)
    {
	    while(!iter->empty()) {
            if (iter->top()->getPresent())
                presents.push_back(iter->top());
            else
                aux.push(iter->top());
            iter->pop();
        }
	    while(!aux.empty())
        {
	        iter->push(aux.top());
	        aux.pop();
        }
    }
	return presents;

}

