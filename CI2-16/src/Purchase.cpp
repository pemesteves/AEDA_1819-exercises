/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {
	Article* a = new Article(client, barCode);
	a->setPresent(present);
	a->setDeliverHome(deliverHome);
	return a;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {
	list<stack<Article*> >::iterator it = bags.begin();
	bool foundBag = false;
	for(; it != bags.end(); it++){
		if (it->size() < BAG_SIZE){
			foundBag = true;
			it->push(article);
			break;
		}
	}

	if(!foundBag){
		stack<Article*> s;
		s.push(article);
		bags.push_back(s);
	}
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
	vector<Article*> presents;
	stack<Article*> tmp_s;
	Article* a;
	for(list<stack<Article*>>::iterator it = bags.begin(); it != bags.end(); it++){
		while(!it->empty()){
			a = it->top();
			it->pop();
			if (!a->getPresent()){
				tmp_s.push(a);
			}
			else{
				presents.push_back(a);
			}
		}
		while(!tmp_s.empty()){
			a = tmp_s.top();
			tmp_s.pop();
			it->push(a);
		}
	}
	return presents;

}

