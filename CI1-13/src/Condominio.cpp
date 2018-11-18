/*
 * Condominio.cpp
 */

#include "Condominio.h"


int Imovel::sequencialID = 1;

Imovel::Imovel(int areaH, string prop): areaHabitacao(areaH), proprietario(prop)
{
	ID = Imovel::sequencialID;
	Imovel::sequencialID++;
}

void Imovel::resetID(){
	Imovel::sequencialID = 1;
}

int Imovel::getID() const
{ return ID; }

void Imovel::setID(int id)
{ ID=id; }

int Imovel::getAreaHabitacao() const
{ return areaHabitacao; }

string Imovel::getProprietario() const
{ return proprietario; }

float Imovel::mensalidade() const{
	return 50+0.2*areaHabitacao;
}

Apartamento::Apartamento(int areaH, int anda, string prop, int id): Imovel(areaH,prop), andar(anda)
{}

float Apartamento::mensalidade() const{
	return Imovel::mensalidade() + 1*andar;
}


Vivenda::Vivenda(int areaH, int areaExt, bool pisc, string prop, int id):Imovel(areaH,prop), areaExterior(areaExt), piscina(pisc)
{}

float Vivenda::mensalidade() const{
	return Imovel::mensalidade() + 0.1*areaExterior + 10*piscina;
}


int Urbanizacao::sequencialID = 1;

Urbanizacao::Urbanizacao(string nm): nome(nm)
{
	ID = Urbanizacao::sequencialID;
	Urbanizacao::sequencialID++;
	Imovel::resetID();
}

void Urbanizacao::resetID(){
	Urbanizacao::sequencialID = 1;
}

void Urbanizacao::adicionaImovel(Imovel *im1)
{ imoveis.push_back(im1); }


vector<Imovel *> Urbanizacao::getImoveis() const
{ return imoveis; }

string Urbanizacao::getNome() const
{ return nome; }

int Urbanizacao::getID() const
{ return ID; }

vector<Imovel *> Urbanizacao::areaSuperiorA(int area1) const{
	vector<Imovel *> v;
	for (size_t i = 0; i < imoveis.size(); i++){
		if (imoveis[i]->getAreaTotal() > area1)
			v.push_back(imoveis[i]);
	}
	return v;
}

bool Urbanizacao::operator> (const Urbanizacao &u1) const{
	int numIm=imoveis.size(), numIm1 = u1.getImoveis().size();
	vector<string> props;
	int numProp;
	for (size_t i = 0; i < imoveis.size(); i++){
		props.push_back(imoveis[i]->getProprietario());
	}
	numProp = numberDifferent(props);
	numIm /= numProp;
	props.resize(0);
	for(size_t i = 0; i < u1.getImoveis().size(); i++){
		props.push_back(u1.getImoveis()[i]->getProprietario());
	}
	numProp = numberDifferent(props);
	numIm1 /= numProp;

	return numIm < numIm1;
}



void ECondominio::adicionaUrbanizacao(Urbanizacao urb1)
{ urbanizacoes.push_back(urb1); }

vector<Urbanizacao> ECondominio::getUrbanizacoes() const
{ return urbanizacoes; }

float ECondominio::mensalidadeDe(string nomeProp) const{
	vector<Imovel *> v;
	float total;
	for (size_t i = 0; i < urbanizacoes.size(); i++){
		v = urbanizacoes[i].getImoveis();
		for(size_t j = 0; j<v.size(); j++){
			if (v[j]->getProprietario()==nomeProp)
				total += v[j]->mensalidade();
		}
	}
	return total;
}

vector<Urbanizacao> ECondominio::removeUrbanizacaoDe(string nomeProp){
	vector<Imovel *> v;
	vector<Urbanizacao> urbRet; vector<Urbanizacao>::iterator it;
	for (it = urbanizacoes.begin(); it != urbanizacoes.end(); it++){
		v = it->getImoveis();
		for (size_t i = 0; i < v.size(); i++){
			if (v[i]->getProprietario() == nomeProp){
				urbRet.push_back(*it);
				urbanizacoes.erase(it);
				it--;
				break;
			}
		}
	}
	return urbRet;
}

vector<Imovel *> ECondominio::operator()(string nomeUrb) const{
	for (size_t i = 0; i < urbanizacoes.size(); i++){
		if (urbanizacoes[i].getNome() == nomeUrb)
			return urbanizacoes[i].getImoveis();
	}
	vector<Imovel *> v;
	return v;
}


