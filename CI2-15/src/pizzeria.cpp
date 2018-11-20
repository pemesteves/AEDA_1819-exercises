/*
 * pizzeria.cpp
 *
 *  Created on: 25 Oct 2015
 *      Author: RRossetti
 */

#include "pizzeria.h"

/*
 * CLASS MENU
 */

Menu::Menu() {
	id = 0;
	name = "";
	likes = 0;
}

int Menu::sequentialID = 1;

Menu::Menu(string n1, vector<string> is1){
	id = Menu::sequentialID;
	Menu::sequentialID++;
	name = n1;
	ingredients = is1;
	likes = 0;
}

Menu::Menu(int id1, string n1, vector<string> is1, int lks1) {
	id = id1;
	name = n1;
	ingredients = is1;
	likes = lks1;
}

int Menu::getId() const { return id; }
void Menu::setId(int id1) { id = id1; }
string Menu::getName() const { return name; }
void Menu::setName(string n1) { name = n1; }
vector<string> Menu::getIngredients() const { return ingredients; }

void Menu::setIngredients(const vector<string> &is1){
	/*if (isSet(is1))
		throw;

	for(size_t i = 0; i < is1.size(); i++){
		ingredients.push_back(is1[i]);
	}*/
}

bool Menu::operator<(const Menu &m1){
	if(likes > m1.getLikes())
		return true;
	else if (likes == m1.getLikes()){
		if(ingredients.size() < m1.getIngredients().size())
			return true;
		else if (ingredients.size() == m1.getIngredients().size()){
			if (name < m1.getName())
				return true;
		}
	}

	return false;
}

/*
 * CLASS CUSTOMER
 */

Customer::Customer(int nif1, string n1) {
	nif = nif1;
	name = n1;
}

int Customer::getNIF() const {
	return nif;
}

string Customer::getName() const {
	return name;
}


/*
 * CLASS PIZZERIA
 */

Pizzeria::Pizzeria() { }

Pizzeria::Pizzeria(vector<Menu> ms1) {
	menus = ms1;
}

vector<Menu> Pizzeria::getMenus() const { return menus; }

vector<Customer*> Pizzeria::getCustomers() const { return customers; }

int Pizzeria::addCustomer(Customer* c1) {
	customers.push_back(c1);
	return customers.size();
}

vector<Menu> Pizzeria::optionsWithinIngredientLimits(int i1, int i2) const{
	if (i1 < 1 || i2 < 1 || i1 > i2)
		throw;
	vector<Menu> v;
	for (size_t i = 0; i < menus.size(); i++){
		if ((int)menus[i].getIngredients().size() >= i1 && (int)menus[i].getIngredients().size() <= i2)
			v.push_back(menus[i]);
	}
	return v;
}

vector<Menu> Pizzeria::popularityRank() const{
	vector<Menu> v = menus;
	insertionSort(v);

	return v;
}

Customer* Pizzeria::chefCustomer(){
	double criatividade = 0;
	int numMenus, likes;
	Customer* c;
	for (size_t i = 0; i < customers.size(); i++){
		numMenus = 0;
		likes = 0;
		for(size_t j = 0; j < menus.size(); j++){
			if(menus[j].getName() == customers[i]->getName()){
				numMenus++;
				likes += menus[j].getLikes();
			}
		}
		if ((double)likes/numMenus > criatividade){
			criatividade = (double)likes/numMenus;
			c = customers[i];
		}
	}

	return c;
}

Menu& Pizzeria::removeIngredient(vector<string> is1, string i1){
	vector<Menu>::iterator it = menus.begin();
	//TODO terminar
}



