#include "Parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli):lotacao(lot),numMaximoClientes(nMaxCli)
{
	vagas = lot;
}

unsigned int ParqueEstacionamento::getNumLugares() const
{
	return lotacao;
}

unsigned int ParqueEstacionamento::getNumMaximoClientes() const
{
	return numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const
{
	for(unsigned int i = 0; i < numMaximoClientes; i++)
	{
		if (clientes[i].nome == nome)
			return i;
	}

	return -1;
}

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
	if (clientes.size() == numMaximoClientes)
		return false;
	else
	{
		InfoCartao cliente;
		cliente.nome = nome;
		cliente.presente = false;
		clientes.push_back(cliente);
		return true;
	}
}

bool ParqueEstacionamento::entrar(const string & nome)
{
	if (vagas == 0)
		return false;
	int pos = posicaoCliente(nome);
	if (pos == -1)
		return false;
	if (clientes[pos].presente == true)
		return false;
	clientes[pos].presente = true;
	vagas--;
	return true;
}

bool ParqueEstacionamento::retiraCliente(const string & nome)
{
	if(posicaoCliente(nome) == -1)
		return false;

	vector<InfoCartao> novosClientes;

	for (size_t i = 0; i < clientes.size(); i++)
	{
		if (clientes.at(i).nome == nome)
			continue;
		else
			novosClientes.push_back(clientes.at(i));
	}

	clientes = novosClientes;

	return true;
}

bool ParqueEstacionamento::sair(const string & nome)
{
	int pos = posicaoCliente(nome);
	if (pos == -1)
		return false;
	if (clientes.at(pos).presente == false)
		return false;

	clientes.at(pos).presente = false;
	vagas++;

	return true;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const
{
	return (lotacao - vagas);
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const
{
	return clientes.size();
}
