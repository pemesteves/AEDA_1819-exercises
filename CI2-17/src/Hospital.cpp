/*
 * Hospital.cpp
 */

#include "Hospital.h"
//
#include <algorithm>


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
	unsigned numPatients = 0;

	for(list<Doctor>::const_iterator it = doctors.begin(); it != doctors.end(); it++){
		if (it->getMedicalSpecialty() == medicalSpecialty){
			numPatients += it->getPatients().size();
		}
	}

	return numPatients;

}


void Hospital::sortDoctors() {
	doctors.sort();
}



bool Hospital::addDoctor(unsigned codM1, string medicalSpecialty1) {
	list<Doctor>::iterator it = doctors.begin();
	unsigned numDoc = 0;
	for(; it != doctors.end(); it++){
		if (it->getMedicalSpecialty() == medicalSpecialty1)
			numDoc++;
	}
	if (numDoc >= 3)
		return false;

	Doctor d(codM1, medicalSpecialty1);
	doctors.push_back(d);
	return true;

}



queue<Patient> Hospital::removeDoctor(unsigned codM1) {
	queue<Patient> p1;
	list<Doctor>::iterator it = doctors.begin();
	for(; it != doctors.end(); it++){
		if (it->getCode() == codM1){
			p1 = it->getPatients();
			doctors.erase(it);
			return p1;
		}
	}

	throw DoctorInexistent();
}


bool Hospital::putInLessBusyDoctor(unsigned cod1, string medicalSpecialty1) {
	list<Doctor>::iterator it = doctors.begin(), it1 = doctors.end();
	for(; it != doctors.end(); it++){
		if (it->getMedicalSpecialty() == medicalSpecialty1){
			if (it1 == doctors.end()){
				it1 = it;
			}
			else{
				if (it->getPatients().size() < it1->getPatients().size())
					it1 = it;
			}
		}
	}
	if (it1 == doctors.end())
		return false;
	Patient p(cod1, medicalSpecialty1);
	it1->addPatient(p);
	return true;

}



void Hospital::processPatient(unsigned codM1) {
	list<Doctor>::iterator it = doctors.begin();
	Patient p(0, "");
	for(; it != doctors.end(); it++){
		if (it->getCode() == codM1){
			p = it->removeNextPatient();
			break;
		}
	}
	if (p.getCode() != 0){
		list<stack<Patient>>::iterator it1 = letterTray.begin();
		bool changed = false;
		for(; it1 != letterTray.end(); it1++){
			if ((*it1).size() != trayCapacity){
				(*it1).push(p);
				changed = true;
				break;
			}
		}
		if(!changed){
			stack<Patient> s;
			s.push(p);
			letterTray.push_back(s);
		}
	}
}


unsigned Hospital::removePatients(unsigned codP1) {
	list<stack<Patient>>::iterator it = letterTray.begin();
	unsigned numDoentes = 0;
	for(; it != letterTray.end(); it++){
		if((*it).top().getCode() == codP1){
			(*it).pop();
			if ((*it).empty()){
				it = letterTray.erase(it);
				it--;
			}
			numDoentes++;
		}
	}
	return numDoentes;

}



