/*
 * BankOfficer.cpp
 */
#include "BankOfficer.h"


BankOfficer::BankOfficer(): id(0) {}

void BankOfficer::setName(string nm){
	name = nm;
}

string BankOfficer::getName() const{
	return name;
}

vector<Account *> BankOfficer::getAccounts() const {
	return myAccounts;
}

void BankOfficer::addAccount(Account *a) {
	myAccounts.push_back(a);
}

unsigned int BankOfficer::getID() const{
	return id;
}


// ----------------------------------------------------------------------------------------------

// a alterar
BankOfficer::BankOfficer(string name) {
    newId++;
    this->name=name;
    this->id=newId;
    this->myAccounts={};
}

bool operator >(BankOfficer left, BankOfficer right)
{
    if(left.getAccounts().size()==right.getAccounts().size())
        return left.getName()>right.getName();
    return left.getAccounts().size()>right.getAccounts().size();
}


