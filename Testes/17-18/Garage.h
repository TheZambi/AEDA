/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>

using namespace std;

class NoSuchBrandException
{
public:
    string brand;
    string getBrand(){return brand;}
    NoSuchBrandException(string brand){this->brand=brand;}
};

template <class Vehicle>
class Garage {
	std::vector<Vehicle *> vehicles;
	const unsigned int capacity;
public:
	Garage(int size);
	~Garage();
	std::vector<Vehicle *> getVehicles() const;
	void setVehicles(std::vector<Vehicle *> vehicles);
	int getCapacity() const;
	bool addVehicle(Vehicle *vehicle);
	Vehicle* removeVehicle(std::string brand, std::string model);
	float avgPrice(std::string brand) const;
	void sortVehicles();
};

class NoSuchVehicleException {
public:
	NoSuchVehicleException() { }
};

template <class Vehicle>
Garage<Vehicle>::Garage(int size) : capacity(size) {
}

template <class Vehicle>
Garage<Vehicle>::~Garage() {
	typename std::vector<Vehicle *>::const_iterator it;
	for (it=vehicles.begin(); it!=vehicles.end(); it++) {
		delete *it;
	}
}

template<class Vehicle>
std::vector<Vehicle *> Garage<Vehicle>::getVehicles() const {
	return vehicles;
}

template<class Vehicle>
void Garage<Vehicle>::setVehicles(std::vector<Vehicle*> vehicles) {
	this->vehicles = vehicles;
}

template<class Vehicle>
int Garage<Vehicle>::getCapacity() const {
	return capacity;
}

template <class Vehicle>
bool Garage<Vehicle>::addVehicle(Vehicle *vehicle)
{
    if((capacity-vehicles.size())==0)
        return false;
    for(size_t i=0; i<vehicles.size();i++)
        if(*vehicle==*vehicles.at(i))
            return false;
    vehicles.push_back(vehicle);
    return true;
}

template <class Vehicle>
bool sortRule(Vehicle* left, Vehicle* right)
{
    if(left->getBrand()==right->getBrand())
        return left->getPrice()>right->getPrice();
    return left->getBrand() < right->getBrand();
}

template <class Vehicle>
void Garage<Vehicle>::sortVehicles()
{
   sort(vehicles.begin(),vehicles.end(),sortRule<Vehicle>);
}

template <class Vehicle>
Vehicle* Garage<Vehicle>::removeVehicle(string brand, string model)
{
    vector<Vehicle*> aux=vehicles;
    for(size_t i=0;i<vehicles.size();i++)
        if((vehicles.at(i)->getBrand()==brand)&&(vehicles.at(i)->getModel()==model))
        {
            vehicles.erase(vehicles.begin()+i);
            return aux.at(i);
        }
    throw NoSuchVehicleException();
}

template <class Vehicle>
float Garage<Vehicle>::avgPrice(string brand) const
{
    float nOcorr=0;
    float total=0.0;
    for(size_t i=0;i<vehicles.size();i++)
        if(vehicles.at(i)->getBrand()==brand)
        {
            total += vehicles.at(i)->getPrice();
            nOcorr++;
        }
    if(nOcorr==0)
        throw NoSuchBrandException(brand);
    return total/nOcorr;
}


#endif /* SRC_GARAGE_H_ */
