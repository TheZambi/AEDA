/*
 * Bank.cpp
 */

#include "Bank.h"
#include <algorithm>
#include <string>

Bank::Bank() {}

void Bank::addAccount(Account *a) {
	accounts.push_back(a);
}

void Bank::addBankOfficer(BankOfficer b){
	bankOfficers.push_back(b);
}

vector<BankOfficer> Bank::getBankOfficers() const {
	return bankOfficers;
}

vector<Account *> Bank::getAccounts() const {
	return accounts;
}


// ----------------------------------------------------------------------------------------------

// a alterar
double Bank::getWithdraw(string cod1) const{
    double total=0;
    for(size_t i=0; i<accounts.size(); i++)
        if(accounts.at(i)->getCodH()==cod1)
             total+=accounts.at(i)->getWithdraw();
	return total;
}


// a alterar
vector<Account *> Bank::removeBankOfficer(string name){
	vector<Account *> res;
	for(size_t i=0; i<bankOfficers.size();i++)
	    if(bankOfficers.at(i).getName()==name)
        {
	        res=bankOfficers.at(i).getAccounts();
	        bankOfficers.erase(bankOfficers.begin()+i);
        }
	return res;
}


// a alterar
const BankOfficer & Bank::addAccountToBankOfficer(Account *ac, string name) {
    BankOfficer *bo= new BankOfficer();
    for(auto iter = bankOfficers.begin(); iter != bankOfficers.end(); iter++)
        if(iter->getName()==name)
        {
            iter->addAccount(ac);
            *bo = *iter;
            return *bo;
        }
    throw NoBankOfficerException(name);

}


// a alterar
void Bank::sortAccounts() {
}

