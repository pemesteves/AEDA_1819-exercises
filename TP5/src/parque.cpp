#include "parque.h"
#include "insertionSort.h"
#include "sequentialSearch.h"
#include <vector>

using namespace std;


ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):
							lotacao(lot), numMaximoClientes(nMaxCli) {
	numClientes = 0;
	vagas=lot;
}

ParqueEstacionamento::~ParqueEstacionamento() {}

vector<InfoCartao> ParqueEstacionamento::getClientes() const { return clientes; }


bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
	if ( numClientes == numMaximoClientes ) return false;
	if ( posicaoCliente(nome) != -1 ) return false;
	InfoCartao info;
	info.nome = nome;
	info.presente = false;
	info.frequencia = 0;  // a fazer
	clientes.push_back(info);
	numClientes++;
	return true;
}

bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	for (vector<InfoCartao>::iterator it = clientes.begin(); it != clientes.end(); it++)
		if ( it->nome == nome ) {
			if ( it->presente == false ) {
				clientes.erase(it);
				numClientes--;
				return true;
			}
			else return false;
		}
	return false;
}

unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return lotacao-vagas;
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if ( vagas == 0 ) return false;
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == true ) return false;
	clientes[pos].presente = true;
	vagas--;
	clientes[pos].frequencia++;
	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if ( pos == -1 ) return false;
	if ( clientes[pos].presente == false ) return false;
	clientes[pos].presente = false;
	vagas++;
	return true;
}


int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	InfoCartao ic1; ic1.nome = nome;
	return sequentialSearch(clientes, ic1);
}

bool InfoCartao::operator == (const InfoCartao &ic1) const{
	if (this->nome == ic1.nome)
		return true;
	else
		return false;
}

int ParqueEstacionamento::getFrequencia(const string &nome) const{
	int posCliente = posicaoCliente(nome);
	if (posCliente == -1)
		throw ClienteNaoExistente(nome);
	return clientes[posCliente].frequencia;
}

void ParqueEstacionamento::ordenaClientesPorFrequencia(){
	insertionSort(clientes);
}

bool InfoCartao::operator < (const InfoCartao &ic1) const{
	if (this->frequencia > ic1.frequencia)
		return true;
	else if(this->frequencia == ic1.frequencia){
		if (this->nome <= ic1.nome)
			return true;
		return false;
	}

	return false;
}

vector<string> ParqueEstacionamento::clientesGamaUso(int n1, int n2){
	ordenaClientesPorFrequencia();
	vector<string> v;
	for (size_t i = 0; i < clientes.size(); i++){
		if (clientes.at(i).frequencia <= n2 ){
			while ((clientes.at(i).frequencia >= n1) && (i < clientes.size())){
				v.push_back(clientes.at(i).nome);
				i++;
			}
			break;
		}
	}

	return v;
}

void ParqueEstacionamento::ordenaClientesPorNome(){
    for (unsigned int i = 1; i < clientes.size(); i++)
    {
    	string tmp = clientes.at(i).nome;
    	int j;
    	for (j = i; j > 0 && tmp < clientes[j-1].nome; j--)
    		clientes[j] = clientes[j-1];
    	clientes[j].nome = tmp;
    }
}

ostream & operator << (ostream &os, const ParqueEstacionamento &pe){
	vector<InfoCartao> v = pe.getClientes();
	for (size_t i = 0; i < v.size(); i++){
		os << v.at(i).nome << ", " << v.at(i).presente << ", " << v.at(i).frequencia << endl;
	}
	return os;
}

InfoCartao ParqueEstacionamento::getClienteAtPos(vector<InfoCartao>::size_type p) const{
	if (p > clientes.size())
		throw PosicaoNaoExistente(p);
	return clientes.at(p);
}

