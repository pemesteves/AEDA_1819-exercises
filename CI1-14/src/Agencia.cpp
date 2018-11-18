/*
 * Agencia.cpp
 */

#include "Agencia.h"


//Conta
Conta::Conta(int nConta, float sd, int nTrans): numConta(nConta), saldo(sd), numTransacoes(nTrans), titular2(NULL)
{ }

int Conta::getNumConta() const
{ return numConta; }

float Conta::getSaldo() const
{ return saldo; }

int Conta::getNumTransacoes() const
{ return numTransacoes; }


void Conta::setTitular2(Cliente *cli2)
{ titular2=cli2; }

Cliente *Conta::getTitular2() const
{ return titular2; }

void Conta::deposito(float valor){
	saldo+=valor;
	numTransacoes++;
}

bool Conta::levantamento(float valor){
	if (saldo < valor)
		return false;
	saldo -= valor;
	numTransacoes++;
	return true;
}

Normal::Normal(int nConta, float sd, int nTrans): Conta(nConta, sd, nTrans)
{}

DeOperacao::DeOperacao(int nConta, float tx, float sd, int nTrans): Conta(nConta, sd, nTrans), taxa(tx)
{}

bool DeOperacao::levantamento(float valor){
	if (valor>30){
		if (saldo < valor+taxa)
			return false;
		saldo -= (valor+taxa);
	}
	else{
		if (saldo < valor)
			return false;
		saldo -= valor;
	}
	numTransacoes++;
	return true;
}


//Cliente
Cliente::Cliente (string nm): nome(nm)
{}

string Cliente::getNome() const
{ return nome; }

vector<Conta *> Cliente::getContas() const
{ return contas; }

void Cliente::adicionaConta(Conta *c1)
{ contas.push_back(c1); }


//Agencia
Agencia::Agencia(string desig): designacao(desig)
{}

string Agencia::getDesignacao() const
{ return designacao; }

vector<Cliente *> Agencia::getClientes() const
{ return clientes; }

vector<Gerente> Agencia::getGerentes() const
{ return gerentes; }

void Agencia::adicionaCliente(Cliente *cli1)
{ clientes.push_back(cli1); }

Conta* Agencia::levantamento(string nomeCli, float valor){
	vector<Conta *> v;
	for (size_t i = 0; i < clientes.size(); i++){
		if (clientes[i]->getNome() == nomeCli){
			v = clientes[i]->getContas();
			break;
		}
	}

	if (v.size() == 0){
		Conta* c = new Conta(-1);
		return c;
	}

	vector<Conta *>::iterator it;
	for (it = v.begin(); it != v.end(); it++){
		if ((*it)->levantamento(valor))
			return *it;
	}
	Conta* c1 = new Conta(-1);
	return c1;
}

float Agencia::fimMes() const{
	float total = 0;
	for(size_t i = 0; i < clientes.size(); i++){
		vector<Conta*> contas = clientes.at(i)->getContas();
		for(size_t j = 0; j < contas.size(); j++){
			if(dynamic_cast<Normal*>(contas.at(j)) != NULL){
				contas.at(j)->levantamento(1.5);
			}
			total += contas.at(j)->getSaldo();
		}
	}
	return total;
}

vector<Conta*> Agencia::removeCliente(string nomeCli){
	vector<Conta*> vetor;
	for(vector<Cliente *>::iterator it = clientes.begin(); it != clientes.end(); it++){
		if ((*it)->getNome() == nomeCli){
			vector<Conta *> v = (*it)->getContas();
			for (vector<Conta*>::iterator it1 = v.begin(); it1 != v.end(); it1++){
				Cliente *c = (*it1)->getTitular2();
				if(c != NULL){
					(*it1)->setTitular2(NULL);
					c->adicionaConta(*it1);
				}
				else{
					vetor.push_back(*it1);
				}
				it1 = v.erase(it1);
				it1--;
			}
			clientes.erase(it);
			break;
		}
	}
	return vetor;
}

bool Agencia::operator< (const Agencia &a1){
	float t1 = 0;
	vector<Conta *> v, vC;
	for (size_t i = 0; i < clientes.size(); i++){
		vC = clientes[i]->getContas();
		for (size_t j = 0; j < vC.size(); j++){
			v.push_back(vC[j]);
			t1 += vC[j]->getSaldo();
		}
	}
	t1 /= clientes.size();
	v.resize(0);
	float t2 = 0;
	vector<Cliente*> v2 = a1.getClientes();
	for (size_t i = 0; i < v2.size(); i++){
		vC = v2[i]->getContas();
		for (size_t j = 0; j < vC.size(); j++){
			v.push_back(vC[j]);
			t2 += vC[j]->getSaldo();
		}
	}
	t2 /= v2.size();
	return t1 < t2;

}

float Agencia::operator()(const string &nome){
	for (size_t i = 0; i < clientes.size(); i++){
		if (clientes[i]->getNome() == nome){
			vector<Conta *> c = clientes[i]->getContas();
			float saldoTotal = 0;
			for (size_t j = 0; j < c.size(); j++)
				saldoTotal += c[j]->getSaldo();
			return saldoTotal;
		}
	}
	return -1;
}

void Agencia::adicionaGerente(string nomeGer){
	Gerente g(nomeGer);
	gerentes.push_back(g);
}

void Agencia::setGerenteID (int IDinicio){
	Gerente::nextID = IDinicio;
}

//Gerente
int Gerente::nextID = 1;

Gerente::Gerente(string nm){
	nome = nm;
	ID = Gerente::nextID;
	Gerente::nextID++;
}

int Gerente::getID() const
{ return ID; }

string Gerente::getNome() const
{ return nome; }



