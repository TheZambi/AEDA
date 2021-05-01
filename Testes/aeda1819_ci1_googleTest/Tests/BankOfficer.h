/*
 * BankOfficer.h
 */

#ifndef SRC_BANKOFFICER_H_
#define SRC_BANKOFFICER_H_

#include "Account.h"
#include <string>
#include <vector>
static int newId=0;

class BankOfficer {
	unsigned int id;
	string name;
	vector<Account *> myAccounts;
public:
	BankOfficer();
	void setName(string nm);
	void addAccount(Account *a);
	void addAccount(vector<Account *> accounts);
	string getName() const;
	vector<Account *> getAccounts() const;
	unsigned int getID() const;
    friend bool operator>(BankOfficer left, BankOfficer right);
	//-------
	BankOfficer(string nm);
	vector<Account *> removeBankOfficer(string name);
};


//exercicio a)
template<class T>
unsigned int numberDifferent (const vector<T> & v1)
{
    vector<T> aux;
    unsigned int numDiff=0;
    for(auto iter=v1.begin(); iter<v1.end();iter++)
    {
        if (!(find(aux.begin(), aux.end(), *iter) != aux.end())) {
            numDiff++;
            aux.push_back(*iter);
        }
    }
    return numDiff;
}
#endif /* SRC_BANKOFFICER_H_ */

