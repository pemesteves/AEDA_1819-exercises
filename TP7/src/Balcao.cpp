#include <queue>
#include <cstdlib>
#include <random>
#include <time.h>
#include "Balcao.h"
#include "exceptions.h"

using namespace std;


Cliente::Cliente() {
	srand(time(NULL));
	numPresentes = rand() % 5 + 1;
}


int Cliente::getNumPresentes() const {
	return numPresentes;
}


Balcao::Balcao(int te): tempo_embrulho(te) {
	srand(time(NULL));
	tempo_atual = 0;
	prox_chegada = rand() % 20 + 1;
	prox_saida = 0;
	clientes_atendidos = 0;
}      


void Balcao:: proximoEvento()
{
	if (!clientes.empty()){
		if (prox_chegada < prox_saida){
			tempo_atual += prox_chegada;
			prox_saida -= prox_chegada;
			chegada();
		}
		else if(prox_saida < prox_chegada){
			tempo_atual += prox_saida;
			prox_chegada -= prox_saida;
			saida();
		}
		else{
			tempo_atual += prox_saida;
			prox_chegada = prox_saida = 0;
			chegada();
			saida();
		}
	}
	else{
		tempo_atual += prox_chegada;
		prox_chegada = prox_saida = 0;
		chegada();
	}
}


void Balcao::chegada()
{
	srand(time(NULL));
	Cliente c;
	clientes.push(c);
	prox_chegada = rand() % 20 + 1;
	if (prox_saida == 0)
		prox_saida = tempo_atual + c.getNumPresentes()*tempo_embrulho;
	cout << "tempo = " << tempo_atual << endl;
	cout << "chegou novo cliente com " << c.getNumPresentes() << " presentes" << endl;
}   


void Balcao::saida()
{
	if (clientes.empty())
		throw FilaVazia();
	Cliente* c = new Cliente();
	*c = getProxCliente();
	clientes.pop();

	if (clientes.empty())
		prox_saida = 0;
	else
		prox_saida = tempo_atual + clientes.front().getNumPresentes()*tempo_embrulho;

	cout << "tempo = " << tempo_atual << endl;
		cout << "chegou novo cliente com " << c->getNumPresentes() << " presentes" << endl;
}


int Balcao::getTempoAtual() const { return tempo_atual; }


int Balcao::getProxChegada() const { return prox_chegada; }


ostream & operator << (ostream & out, const Balcao & b1)
{
	out << b1.clientes_atendidos << endl;
	out << b1.clientes.size() << endl;
	return out;
}


int Balcao::getTempoEmbrulho() const {
	return tempo_embrulho;
}


int Balcao::getProxSaida() const {
	return prox_saida;
}


int Balcao::getClientesAtendidos() const {
	return clientes_atendidos;
}


Cliente & Balcao::getProxCliente() {
	if (clientes.empty())
		throw FilaVazia();
	Cliente *c = new Cliente();
	*c = clientes.front();
	return *c;
}


