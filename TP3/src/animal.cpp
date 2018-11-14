#include "animal.h"
#include <sstream>

int Animal::maisJovem = 100000;

int Animal::getMaisJovem(){
	return maisJovem;
}

Animal::Animal(string nome, int idade){
	this->nome = nome;
	this->idade = idade;
	if (idade < getMaisJovem())
		Animal::maisJovem = idade;
	this->vet = NULL;
}

string Animal::getNome() const {
	return nome;
}

string Animal::getInformacao(){
	ostringstream oss;
	oss << nome << ", " << idade;
	if (vet != NULL)
		oss << ", " << vet->getInformacao();

	return oss.str();
}

int Animal::getIdade() const {
	return idade;
}

Veterinario* Animal::getVeterinario(){
	return vet;
}


Cao::Cao(string nome, int idade, string raca): Animal(nome, idade){
	this->raca = raca;
}

bool Cao::eJovem()const{
	if (idade < 5)
		return 1;
	return 0;
}

string Cao::getInformacao(){
	ostringstream oss;
	oss << Animal::getInformacao() << ", " << raca;

	return oss.str();
}

Voador::Voador(int vmax, int amax){
	this->altura_max = amax;
	this->velocidade_max = vmax;
}

string Voador::getInformacao() const{
	ostringstream oss;
	oss << velocidade_max << ", " << altura_max;

	return oss.str();
}

Morcego::Morcego(string nome, int idade, int vmax, int amax):
		Animal(nome, idade), Voador(vmax, amax){}

bool Morcego::eJovem()const{
	if(idade < 4)
		return 1;
	return 0;
}

string Morcego::getInformacao(){
	ostringstream oss;
	oss << Animal::getInformacao() << ", " << Voador::getInformacao();

	return oss.str();
}
