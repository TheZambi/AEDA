/*
 * Hospital.cpp
 */
#include <iostream>
#include "Hospital.h"
//
#include <algorithm>

using namespace std;

Hospital::Hospital(unsigned trayC):trayCapacity(trayC)
{ }

void Hospital::addDoctor(const Doctor &d1) {
	doctors.push_back(d1);
}

list<Doctor> Hospital::getDoctors() const {
	return doctors;
}

void Hospital::addTrays(stack<Patient> tray1) {
	letterTray.push_back(tray1);
}

list<stack<Patient> > Hospital::getTrays() const {
	return letterTray;
}



unsigned Hospital::numPatients(string medicalSpecialty) const
{
    unsigned int count = 0;
	for(auto x = doctors.begin(); x != doctors.end(); x++)
    {
        if((*x).getMedicalSpecialty() == medicalSpecialty)
            count += (*x).getPatients().size();
    }
	return count;

}

bool sortRule(Doctor d1, Doctor d2)
{
    if(d1.getPatients().size()==d2.getPatients().size()) {
        if (d1.getMedicalSpecialty() == d2.getMedicalSpecialty())
            return d1.getCode() < d2.getCode();
        return (d1.getMedicalSpecialty() < d2.getMedicalSpecialty());
    }
    return d1.getPatients().size()<d2.getPatients().size();
}

void Hospital::sortDoctors() {
	// TODO
	doctors.sort(sortRule);
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
    int counter=0;
	for(auto iter=doctors.begin();iter!=doctors.end();iter++)
    {
	    if(iter->getMedicalSpecialty()==medicalSpecialty1)
	        counter++;
    }
	if (counter>=3)
	    return false;
	doctors.push_back((Doctor(codM1,medicalSpecialty1)));
	return true;

}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	// TODO
	queue<Patient> p1;
    for(auto iter=doctors.begin();iter!=doctors.end();iter++)
    {
        if(iter->getCode()==codM1)
        {
                p1 = iter->getPatients();
                doctors.erase(iter);
                return p1;
        }
    }
	throw DoctorInexistent();

}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
	// TODO
	list<Doctor>::iterator toSave=doctors.begin();
	for(auto iter=doctors.begin()++;iter!=doctors.end();iter++)
    {
	    if(iter->getPatients().size()<toSave->getPatients().size()&&iter->getMedicalSpecialty()==medicalSpecialty1)
	        toSave=iter;
    }
    toSave->addPatient(Patient(cod1,medicalSpecialty1));
    if(toSave==doctors.begin() && toSave->getMedicalSpecialty()!=medicalSpecialty1)
        return false;
	return true;

}



void Hospital::processPatient(unsigned codM1) {
	// TODO
	list<Doctor>::iterator it=doctors.begin();
	for(auto iter=doctors.begin();iter!=doctors.end();iter++)
    {
	    if(iter->getCode()==codM1){

	        it=iter;
	        break;}
    }
	if(it==doctors.begin() && it->getCode()!=codM1)
	    return;
    if(it->getPatients().size()==0)
        return;
    Patient removed = it->removeNextPatient();
    for(auto iter=letterTray.begin();iter!=letterTray.end();iter++)
        if(iter->size()<trayCapacity){
            iter->push(removed);
            return;
        }

    stack<Patient> newStack;
    newStack.push(removed);
    letterTray.push_back((newStack));
}


unsigned Hospital::removePatients(unsigned codP1) {
    // TODO
    int toRet = 0;
    for (auto iter = letterTray.begin(); iter != letterTray.end(); iter++) {
        if (iter->top().getCode() == codP1) {
            toRet++;
            iter->pop();
        }
    }
    while (letterTray.front().size() == 0) {
        letterTray.erase(letterTray.begin());
    }

    list<stack<Patient>>::iterator iter = letterTray.begin();
    if (letterTray.size() > 0) {
        while (iter != letterTray.end()) {
            if (iter->size() == 0) {
                iter=letterTray.erase(iter);
            }
            else
                iter++;
        }
    }
	return toRet;

}



