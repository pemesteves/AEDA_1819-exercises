/*
 * Postman.cpp
 */
#include "Postman.h"

unsigned int Postman::nId = 0;

Postman::Postman(): id(0){};

Postman::Postman(string name): id(++nId){
	this->name = name;
}


void Postman::setName(string nm){
	name = nm;
}

string Postman::getName() const{
	return name;
}

vector<Mail *> Postman::getMail() const {
	return myMail;
}

void Postman::addMail(Mail *m) {
	myMail.push_back(m);
}

void Postman::addMail(vector<Mail *> mails) {
	myMail.insert(myMail.end(),mails.begin(),mails.end());
}

unsigned int Postman::getID() const{
	return id;
}

bool Postman::operator< (const Postman &p) const{
	vector<string> v1, v2;
	for(size_t i = 0; i < myMail.size(); i++){
		v1.push_back(myMail[i]->getZipCode());
	}
	unsigned int n1 = numberDifferent(v1);
	vector<Mail *> v = p.getMail();
	for (size_t i = 0; i < v.size(); i++){
		v2.push_back(v[i]->getZipCode());
	}
	unsigned int n2 = numberDifferent(v2);
	return n1 < n2;
}


