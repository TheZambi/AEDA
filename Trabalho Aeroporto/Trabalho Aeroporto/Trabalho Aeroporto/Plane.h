#pragma once

#include "Flight.h"

using namespace std;

class Flight;

class capacityError
{
public:
	int inputCapacity;
	capacityError(int inputCapacity) { this->inputCapacity = inputCapacity;}
	friend ostream & operator <<(ostream &out, const capacityError &error);
};

class Plane
{
private:
	string type; //para simplificar apenas existem modelos A, B, C.
	int capacity;
	vector<Flight*> flights; //n?o esquecer de usar new
	double expenses;
public:
	Plane(string type, int capacity, vector<Flight*> &flights);
	double calcExp(string type, vector<Flight*> &flights) const;
	string getType() const;
	int getCapacity() const;
	vector<Flight*> getFlights() const;
	void setCapacity(int cap);
	bool setFlights(vector<Flight*> fly);
};