/*
 * Postman.h
 */

#ifndef SRC_POSTMAN_H_
#define SRC_POSTMAN_H_

#include "Mail.h"
#include <string>
#include <vector>
#include <algorithm>

class Postman {
	unsigned int id;
	static unsigned int nId;
	string name;
	vector<Mail *> myMail;
public:
	Postman();
	Postman(string name);
	static unsigned int idInc();
	void setName(string nm);
	void addMail(Mail *m);
	void addMail(vector<Mail *> mails);
	string getName() const;
	vector<Mail *> getMail() const;
	unsigned int getID() const;
	bool operator< (const Postman &p) const;
};

template<class T>
unsigned int numberDifferent (const vector<T> &v1){
	vector<T> v2 = v1;
	sort(v2.begin(), v2.end());

	T tmp;
	unsigned int nD = 0;
	for (size_t i = 0; i < v2.size(); i++){
		if (tmp != v2.at(i))
			nD++;
		tmp = v2.at(i);
	}

	return nD;
}

#endif /* SRC_POSTMAN_H_ */
