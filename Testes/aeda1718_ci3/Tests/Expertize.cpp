/*
 * Expertize.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "Expertize.h"
#include <vector>


Expertize::Expertize(string name, unsigned cost) : name(name), cost(cost) {
}

string Expertize::getName() const {
	return this->name;
}

unsigned Expertize::getCost() const {
	return this->cost;
}

vector<Student*> Expertize::getConsultants() const {
	return this->consultants;
}

void Expertize::setConsultants(vector<Student*> students) {
	this->consultants = students;
}

void Expertize::addConsultant(Student* student) {
	this->consultants.push_back(student);
}

bool Expertize::operator<(const Expertize &exp1) const {
	if(this->getName()<exp1.getName())
	    return true;
	else if(this->getName()>exp1.getName())
	    return false;
	return this->getCost()<exp1.getCost();
}

bool Expertize::operator==(const Expertize &exp1) const {
	return this->getName()==exp1.getName();
}
