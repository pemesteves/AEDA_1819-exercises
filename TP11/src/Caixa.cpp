/*
 * Caixa.cpp
 */

#include "Caixa.h"
#include <sstream>

Objeto::Objeto(unsigned idObj, unsigned pesoObj): id(idObj), peso(pesoObj)
{}

unsigned Objeto::getID() const {
	return id;
}

unsigned Objeto::getPeso() const {
	return peso;
}

Caixa::Caixa(unsigned cap): id(ultimoId++), capacidade(cap), cargaLivre(cap)
{}

unsigned Caixa::getID() const {
	return id;
}

unsigned Caixa::getCargaLivre() const {
	return cargaLivre;
}

void Caixa::addObjeto(Objeto& obj) {
	cargaLivre -= obj.getPeso();
	objetos.push(obj);
}

void Caixa::resetID(){
	ultimoId = 1;
}

unsigned Caixa::getSize() const {
	return objetos.size();
}


ostream& operator<<(ostream& os, Objeto obj) {
	os << "O" << obj.id << ": " << obj.peso;
	return os;
}

unsigned Caixa::ultimoId = 1;


/* a implementar pelos estudantes */

bool Objeto::operator<(const Objeto& o1) const {
	if (peso < o1.getPeso())
		return true;
	return false;
}

bool Caixa::operator<(const Caixa& c1) const {
	if(cargaLivre > c1.getCargaLivre())
		return true;
	return false;
}


string Caixa::imprimeConteudo() const {
	STACK_OBJS obj = objetos;
	ostringstream oss;
	if(obj.size() == 0)
		oss << "Caixa " << id << " vazia!\n";
	else{
		oss << "C" << id << "[";
		while(!obj.empty()){
			oss << " " << obj.top();
			obj.pop();
		}
		oss << " ]";
	}
	return oss.str();
}


