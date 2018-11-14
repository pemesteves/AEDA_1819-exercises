#include "veterinario.h"
#include <sstream>


Veterinario::Veterinario(string nome, int cod){
	this->nome = nome;
	this->codOrdem = cod;
}

string Veterinario::getNome() const {
	return nome;
}

string Veterinario::getInformacao(){
	ostringstream oss;
	oss << nome  << ", " << codOrdem << ", ";

	return oss.str();
}

