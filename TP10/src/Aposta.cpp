#include "Aposta.h"
#include <iostream>
#include <sstream>

using namespace std;

bool Aposta::contem(unsigned num) const
{
	if (numeros.find(num) != numeros.end())
		return true;
	return false;
}


void Aposta::geraAposta(const vector<unsigned> & valores, unsigned n)
{
	unsigned initialSize;
	unsigned m = 0;
	unsigned index = 0;

	while(m < n){
		initialSize = numeros.size();

		numeros.insert(valores[index]);

		if(numeros.size() != initialSize){
			m++;
		}

		index++;
	}
}


unsigned Aposta::calculaCertos(const tabHInt & sorteio) const
{
	unsigned certos = 0;
	for(tabHInt::const_iterator it = sorteio.begin(); it != sorteio.end(); it++){
		if(numeros.find(*it) != numeros.end())
			certos++;
	}

	return certos;
}

bool Aposta::operator==(const Aposta &a1) const{
	if(numeros == a1.getNumeros())
		return true;
	return false;
}



