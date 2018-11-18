/*
 * Condominio.h
 */

#ifndef CONDOMINIO_H_
#define CONDOMINIO_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Imovel {
	int areaHabitacao;
	string proprietario;
	int ID;
	static int sequencialID;
public:
	Imovel(int areaH, string prop);
	static void resetID();
	int getID() const;
	int getAreaHabitacao() const;
	string getProprietario() const;
	void setID(int id);
	virtual float mensalidade() const;
	virtual int getAreaTotal() const {return areaHabitacao;}
};

class Apartamento: public Imovel {
	int andar;
public:
	Apartamento(int areaH, int anda, string prop, int id=0);
	float mensalidade() const;
	int getAreaTotal() const {return Imovel::getAreaHabitacao();}
};

class Vivenda: public Imovel {
   int areaExterior;
   bool piscina;
public:
   Vivenda(int areaH, int areaExt, bool pisc, string prop, int id=0);
   float mensalidade() const;
   int getAreaTotal() const {return Imovel::getAreaHabitacao()+areaExterior;}
};


class Urbanizacao {
	string nome;
	int ID;
	vector<Imovel *> imoveis;
	static int sequencialID;
public:
	Urbanizacao(string nm);
	static void resetID();
	void adicionaImovel(Imovel *im1);
	vector<Imovel *> getImoveis() const;
	string getNome() const;
	int getID() const;
	vector<Imovel *> areaSuperiorA(int area1) const;
	bool operator> (const Urbanizacao &u1) const;
};


class ECondominio {
	vector<Urbanizacao> urbanizacoes;
public:
	void adicionaUrbanizacao(Urbanizacao urb1);
	vector<Urbanizacao> getUrbanizacoes() const;
	float mensalidadeDe(string nomeProp) const;
	vector<Urbanizacao> removeUrbanizacaoDe(string nomeProp);
	vector<Imovel *> operator()(string nomeUrb) const;
};

template<class T>
unsigned int numberDifferent (const vector<T> &v1){
	vector<T> v2 = v1;
	sort(v2.begin(), v2.end());

	T tmp;
	unsigned int nD = 0;
	for (size_t i = 0; i < v2.size(); i++){
		if (tmp != v2.at(i))
			nD++;
		tmp = v2.at(i);
	}

	return nD;
}

#endif /* CONDOMINIO_H_ */
