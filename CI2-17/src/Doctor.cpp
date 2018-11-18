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
	queue<Patient> p1, pFinal;
	Patient p(0, "");
	while(!patients.empty()){
		if (patients.front().getCode() == codP1){
			pFinal.push(patients.front());
			patients.pop();
			while(!p1.empty()){
				p = p1.front();
				p1.pop();
				pFinal.push(p);
			}
			while(!patients.empty()){
				p = patients.front();
				patients.pop();
				pFinal.push(p);
			}
			patients = pFinal;
			break;
		}

		p = patients.front();
		patients.pop();
		p1.push(p);
	}
	if (pFinal.empty())
		patients = p1;
}

bool Doctor::operator<(const Doctor &d1){
	if (patients.size() < d1.getPatients().size())
		return true;
	if (patients.size() == d1.getPatients().size()){
		if (medicalSpecialty < d1.getMedicalSpecialty())
			return true;
		if(medicalSpecialty == d1.getMedicalSpecialty()){
			if (codeM < d1.getCode())
				return true;
		}
	}

	return false;
}

