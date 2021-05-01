/*
 * Doctor.cpp
 */

#include "Doctor.h"


Patient::Patient(unsigned codP, string mS): codeP(codP), medicalSpecialty(mS)
{}

string Patient::getMedicalSpecialty() const {
	return medicalSpecialty;
}

unsigned Patient::getCode() const {
	return codeP;
}

Doctor::Doctor(unsigned codM, string mS): codeM(codM), medicalSpecialty(mS)
{}


Doctor::Doctor(unsigned codM, string mS, queue<Patient> patients1): codeM(codM), medicalSpecialty(mS), patients(patients1)
{}

unsigned Doctor::getCode() const {
	return codeM;
}

string Doctor::getMedicalSpecialty() const {
	return medicalSpecialty;
}

queue<Patient> Doctor::getPatients() const {
	return patients;
}

void Doctor::addPatient(const Patient &p1) {
	patients.push(p1);
}

Patient Doctor::removeNextPatient() {
	if (!patients.empty()) {
		Patient p1 = patients.front();
		patients.pop();
		return p1;
	}
	else throw PatientInexistent();
}




void Doctor::moveToFront(unsigned codP1) {
    // TODO
    queue<Patient> aux, final;
    int size=patients.size();
    for (size_t i = 0; i < size; i++) {
        if (patients.front().getCode() == codP1) {
            final.push(patients.front());
            patients.pop();
            break;
        }
        else {
            aux.push(patients.front());
            patients.pop();
        }
    }
    if(final.size()==0)
    {
        patients=aux;
        return;
    }
    size=aux.size();
    for(size_t i=0;i<size;i++) {
        final.push(aux.front());
        aux.pop();
    }
    size=patients.size();
    for(size_t i=0;i<size;i++) {
        final.push(patients.front());
        patients.pop();
    }
    patients=final;
}
