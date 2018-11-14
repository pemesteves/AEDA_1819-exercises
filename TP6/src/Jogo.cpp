/*
 * Jogo.cpp
 *
 */

#include "Jogo.h"
#include <random>
#include <time.h>

using namespace std;

int Jogo::numPalavras(string frase)
{
	if ( frase.length() == 0 ) return 0;
	int n=1;
	unsigned pos = frase.find(' ');
	while ( pos != string::npos ) {
		frase = frase.substr(pos+1);
		pos = frase.find(' ');
		n++;
	}
	return n;
}


Jogo::Jogo()
{
	this->criancas.clear();
}

Jogo::Jogo(list<Crianca>& lc2)
{
	this->criancas = lc2;
}

void Jogo::insereCrianca(const Crianca &c1)
{
	this->criancas.push_back(c1);
}

list<Crianca> Jogo::getCriancasJogo() const
{
	return criancas;
}


string Jogo::escreve() const
{
	ostringstream oss;
	list<Crianca>::const_iterator it = criancas.begin();
	for(; it != criancas.end(); it++){
		oss << it->escreve() << endl;
	}

	string res = oss.str();
	return res;
}


Crianca& Jogo::perdeJogo(string frase)
{
	Crianca *c1 = new Crianca();
	list<Crianca> l = getCriancasJogo();
	list<Crianca>::iterator it;

	int numPal = numPalavras(frase) - 1;
	while(l.size() > 1){
		it = l.begin();
		for(int i = 1; i <= numPal; i++){
			it++;
			if (it == l.end())
				it = l.begin();
		}
		l.erase(it);
	}
	it = l.begin();

	*c1 = *it;

	return *c1;
}


list<Crianca>& Jogo::inverte()
{
	criancas.reverse();
	return criancas;
}


list<Crianca> Jogo::divide(unsigned id)
{
	list<Crianca>::iterator it = criancas.begin();

	list<Crianca> res;

	for(; it != criancas.end(); it++){
		if ((*it).getIdade() > id){
			res.push_back(*it);
			it = criancas.erase(it);
			it--;
		}
	}

	return res;
}


void Jogo::setCriancasJogo(const list<Crianca>& l1)
{
	list<Crianca>::const_iterator it;
	for(it = l1.begin(); it != l1.end(); it++)
		this->criancas.push_back(*it);
}


bool Jogo::operator==(Jogo& j2){
	list<Crianca> l2 = j2.getCriancasJogo();
	if (criancas.size() != l2.size())
		return false;
	list<Crianca>::iterator it = criancas.begin();
	list<Crianca>::iterator it2 = l2.begin();
	for(; it != criancas.end(); it++){
		if (!((*it) == (*it2))){
			return false;
		}
		it2++;
	}
	return true;
}


list<Crianca> Jogo::baralha() const
{
	srand(time(NULL));
	int numCriancas = criancas.size();
	unsigned int novoNumCriancas = 0;
	int randCria = 0;

	list<Crianca> res, newL = criancas;
	list<Crianca>::iterator it;

	for(int i = 0; i < numCriancas; i++){
		it = newL.begin();
		novoNumCriancas = newL.size();
		randCria = rand() % numCriancas;
		while(randCria > 0){
			it++;
			randCria--;
		}
		res.push_back(*it);
		newL.erase(it);
	}

	return res;
}
