#include "Frota.h"
#include <string>

using namespace std;

int Frota::menorAno() const
{
	if (numVeiculos() == 0)
		return 0;

	int menorAno = veiculos[0]->getAno();

	for (int i = 1; i < numVeiculos(); i++){
		if (veiculos[i]->getAno() < menorAno)
			menorAno = veiculos[i]->getAno();
	}

	return menorAno;
}

ostream & operator<<(ostream & o, const Frota & f){
	for (int i = 0; i < f.numVeiculos(); i++){
		f.veiculos.at(i)->info();
	}
	return o;
}

vector<Veiculo *> Frota::operator () (int anoM) const{
	vector <Veiculo *> v;
	for (int i = 0; i < numVeiculos(); i++){
		if (veiculos.at(i)->getAno() == anoM)
			v.push_back(veiculos.at(i));
	}

	return v;
}

float Frota::totalImposto() const{
	float totalImposto = 0;

	for (int i = 0; i < numVeiculos(); i++){
		totalImposto += veiculos.at(i)->calcImposto();
	}

	return totalImposto;
}
