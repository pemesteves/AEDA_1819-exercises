/*
 * Garage.h
 *
 *  Created on: 24/10/2017
 *      Author: hlc
 */

#ifndef SRC_GARAGE_H_
#define SRC_GARAGE_H_

#include <vector>

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

class NoSuchBrandException{
	std::string brand;
public:
	NoSuchBrandException(std::string b){brand=b;}
	std::string getBrand(){return brand;}
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

template<class Vehicle>
bool Garage<Vehicle>::addVehicle(Vehicle *vehicle){
	if (vehicles.size() == capacity)
		return false;

	for (size_t i = 0; i < vehicles.size(); i++){
		if (*vehicles[i] == *vehicle)
			return false;
	}

	vehicles.push_back(vehicle);
	return true;
}


template<class Vehicle>
bool compareVehicle(Vehicle* a, Vehicle* b){
	return ((*a)<(*b));
}

template<class Vehicle>
void Garage<Vehicle>::sortVehicles(){
	using namespace std;
	sort(vehicles.begin(), vehicles.end(), compareVehicle<Vehicle>);
}

template<class Vehicle>
Vehicle* Garage<Vehicle>::removeVehicle(std::string brand, std::string model){
	using namespace std;
	typename vector<Vehicle*>::iterator it;
	for (it = vehicles.begin(); it != vehicles.end(); it++){
		if ((*it)->getBrand() == brand && (*it)->getModel() == model){
			Vehicle* v = *it;
			vehicles.erase(it);
			return v;
		}
	}
	throw NoSuchVehicleException();
}

template<class Vehicle>
float Garage<Vehicle>::avgPrice(std::string brand) const{
	float avg = 0;
	float num = 0;
	for (size_t i = 0; i < vehicles.size(); i++){
		if (vehicles[i]->getBrand() == brand){
			num++;
			avg += vehicles[i]->getPrice();
		}
	}

	if (num == 0)
		throw NoSuchBrandException(brand);

	return avg/num;
}

#endif /* SRC_GARAGE_H_ */
