/*
 * PostOffice.cpp
 */

#include "PostOffice.h"
#include <string>

PostOffice::PostOffice(string firstZCode, string lastZCode):
								firstZipCode(firstZCode), lastZipCode(lastZCode)
{}
PostOffice::PostOffice() {}

void PostOffice::addMailToSend(Mail *m) {
	mailToSend.push_back(m);
}

void PostOffice::addMailToDeliver(Mail *m) {
	mailToDeliver.push_back(m);
}

void PostOffice::addPostman(const Postman &p){
	postmen.push_back(p);
}

vector<Mail *> PostOffice::getMailToSend() const {
	return mailToSend;
}

vector<Mail *> PostOffice::getMailToDeliver() const {
	return mailToDeliver;
}

vector<Postman> PostOffice::getPostman() const {
	return postmen;
}

vector<Mail *> PostOffice::removePostman(string name){
	vector<Postman>::iterator it = postmen.begin();
	vector<Mail *> v;
	for (; it != postmen.end(); it++){
		if (it->getName() == name){
			v = it->getMail();
			postmen.erase(it);
			break;
		}
	}
	return v;
}

vector<Mail *> PostOffice::endOfDay(unsigned int &balance){
	balance = 0;
	vector<Mail *> v;
	for (size_t i = 0; i < mailToSend.size(); i++){
		balance += mailToSend[i]->getPrice();
		if (mailToSend[i]->getZipCode() >= firstZipCode && mailToSend[i]->getZipCode() <= lastZipCode)
			addMailToDeliver(mailToSend[i]);
		else
			v.push_back(mailToSend[i]);
	}
	mailToSend.resize(0);
	return v;
}

Postman PostOffice::addMailToPostman(Mail *m, string name){
	for (size_t i = 0; i < postmen.size(); i++){
		if (postmen[i].getName() == name){
			postmen[i].addMail(m);
			return postmen[i];
		}
	}

	throw NoPostmanException(name);
}

