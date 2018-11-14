#include "zoo.h"
#include <sstream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

int Zoo::numAnimais() const {
	return animais.size();
}

int Zoo::numVeterinarios() const {
	return veterinarios.size();
}

void Zoo::adicionaAnimal(Animal *a1){
	animais.push_back(a1);
}

string Zoo::getInformacao() const{
	ostringstream oss;
	for (size_t i = 0; i < animais.size(); i++){
		oss << animais.at(i)->getInformacao() << endl;
	}

	return oss.str();
}

bool Zoo::animalJovem(string nomeA){
	for (size_t i = 0; i < animais.size(); i++){
		if (animais.at(i)->getNome() == nomeA){
			if (animais.at(i)->eJovem())
				return true;
		}
	}

	return false;
}

void Zoo::alocaVeterinarios(istream &isV){
	string nome, codigo;
	while(!isV.eof()){
		getline(isV, nome);
		getline(isV, codigo);
		long cod = atoi(codigo.c_str());
		Veterinario *v = new Veterinario(nome, cod);
		veterinarios.push_back(v);
	}
	/*
	for (size_t i = 0; (i < animais.size())||(i<veterinarios.size()); i++){
		animais.at(i)->vet = veterinarios.at(i);
	}*/
}

bool Zoo::removeVeterinario (string nomeV){
	vector<Veterinario *>::iterator it = veterinarios.begin();
	size_t size = veterinarios.size();

	for (; it != veterinarios.end(); it++){
		if ((*it)->getNome() == nomeV){
			it = veterinarios.erase(it);
			break;
		}
	}

	if (size == veterinarios.size())
		return false;

	Veterinario* v;

	for(vector<Animal *>::iterator aIt = animais.begin(); aIt != animais.end(); aIt++){
		v = (*aIt)->getVeterinario();
		if (v->getNome() == nomeV){
			v = *it;
		}
	}

	return true;
}

bool Zoo::operator<(Zoo& zoo2) const{
	int idade1 = 0, idade2 = 0;

	for (size_t i = 0; i < animais.size(); i++){
		idade1 += animais.at(i)->getIdade();
	}

	for (int i = 0; i < zoo2.numAnimais(); i++){
		idade2 += zoo2.animais.at(i)->getIdade();
	}


	if (idade1 < idade2)
		return true;

	return false;
}
