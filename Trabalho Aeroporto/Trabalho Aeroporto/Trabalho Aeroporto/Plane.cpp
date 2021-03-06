#include "Plane.h"


double Plane::calcExp(string type, vector<Flight*> &flights) const
{
	double total = 0;
	if (type == "A")
		total = 100.0 + flights.size() * 100.0;
	if (type == "B")
		total = 150.0 + flights.size() * 100.0;
	if (type == "C")
		total = 200.0 + flights.size() * 100.0;
	for (size_t i = 0; i < flights.size(); ++i)
		total += flights.at(i)->getFlightDuration().getTotalMinutes()*5;
	return total;
}

string Plane::getType() const
{
	return type;
}

int Plane::getCapacity() const
{
	return capacity;
}

vector<Flight*> Plane::getFlights() const
{
	return flights;
}

Plane::Plane(string type, int capacity, vector<Flight*> &flights)
{
	this->type = type;
	this->capacity = capacity;
	this->flights = flights;
	this->expenses = calcExp(type, flights);
}

ostream & operator <<(ostream &out, const capacityError &error)
{
	out << "Exeption was thrown trying to set the plane's capacity. Capacity received :" << error.inputCapacity; return out;
}

void Plane::setCapacity(int cap)
{
	if (cap < 0)
		throw capacityError(cap);
	capacity = cap;
}

bool Plane::setFlights(vector<Flight*> fly)
{
	flights = fly;
	return true;
}