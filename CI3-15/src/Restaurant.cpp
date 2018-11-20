/*
 * Restaurant.cpp
 *
 *  Created on: 17/11/2015
 *      Author: hlc
 */

#include "Restaurant.h"
#include <iostream>

using namespace std;

Restaurant::Restaurant() { }

Restaurant::Restaurant(vector< stack<Dish*> >* cl, queue<Dish*>* di, list<Dish*>* dr) {
	if(cl != NULL) clean = *cl;
	if(di != NULL) dirty = *di;
	if(dr != NULL) drying = *dr;
}

void Restaurant::addTable(unsigned int n_places) {
	tables.push_back(Table(n_places));
}

void Restaurant::addTable(Table& t) {
	tables.push_back(t);
}

const Table& Restaurant::getTable(vector<Table>::size_type idx) const {
	return tables[idx];
}

/**
 * Gets the clean dishes stack for a given collection and type.
 * If there is none, adds and returns an empty stack.
 */
stack<Dish*>& Restaurant::getCleanDishStack(string collection, TypeOfDish type) {

	for(vector< stack<Dish*> >::iterator it = clean.begin(); it != clean.end(); ++it) {
		if((*it).empty() || ((*it).top()->getCollection() == collection && (*it).top()->getType() == type)){
			return *it;
		}
	}

	stack<Dish*> st;
	clean.push_back(st);
	return clean.back();
}

const queue<Dish*>& Restaurant::getDirty() const {
	return dirty;
}

const list<Dish*>& Restaurant::getDrying() const {
	return drying;
}

/**
 * Adds a number of dishes of a collection/type to the respective clean stack.
 */
void Restaurant::addDishes(unsigned int n, string collection, TypeOfDish type) {
	stack<Dish*>* s = new stack<Dish*>;
	*s = getCleanDishStack(collection, type);
	Dish* d = new Dish(collection, type);
	while(n > 0){
		s->push(d);
		n--;
	}
}

/**
 * Washes a dish, getting if from the dirty queue and putting it in the wet list.
 * Returns the washed dish.
 */
Dish* Restaurant::washDish() {
	Dish* d;
	if (!dirty.empty()){
		d = dirty.front();
		dirty.pop();
		drying.push_back(d);
	}
	return d;
}

/**
 * Clears a table, placing all dishes that are on it in the dirty queue.
 */
void Restaurant::clearTable(vector<Table>::size_type idx) {
	if (idx < tables.size() && idx >= 0){
		vector<Dish*> d;
		d = tables.at(idx).clear();
		for(size_t i = 0; i < d.size(); i++){
			dirty.push(d[i]);
		}
	}
}

/**
 * Stores in the respective clean stack all drying dishes of a given collect
 * ion and type.
 */
void Restaurant::storeDryDishes(string collection, TypeOfDish type) {
	list<Dish*>::iterator it = drying.begin();
	vector<Dish*> v;
	for(; it != drying.end(); it++){
		if((*it)->getCollection() == collection && (*it)->getType() == type){
			v.push_back(*it);
			it = drying.erase(it);
			it--;
		}
	}
	bool foundStack = false;
	for(size_t i = 0; i < clean.size(); i++){
		if (!clean.at(i).empty()){
			if (clean[i].top()->getCollection() == collection){
				for(size_t j = 0; j < v.size(); j++){
					clean[i].push(v[j]);
				}
				foundStack = true;
				break;
			}
		}
	}
	if(!foundStack){
		stack<Dish*> s;
		for(size_t i = 0; i <v.size(); i++){
			s.push(v[i]);
		}
		clean.push_back(s);
	}

}

/**
 * Puts Plates of a given collection in a table.
 * Throws TableNotReadyException when the table is not empty.
 * Throws NotEnoughDishesException when there are not enough clean plates of the collection.
 */
void Restaurant::setupTable(vector<Table>::size_type idx, string collection) {

	// TODO

}

/**
 * Picks the dry dishes and groups them.
 * Returns the grouped dishes.
 */
list<Dish*> Restaurant::pickupAndGroupDryDishes() {
	list<Dish*> dry_grouped;

	// TODO

	return dry_grouped;
}

/**
 * Stores grouped dishes in the respective clean stacks.
 * Returns the number of stacks that have been updated.
 */
int Restaurant::storeGroupedDishes(list<Dish*> grouped_dishes) {

	// TODO

	return 0;
}

