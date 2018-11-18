/*
 * Agencia.h
 */

#ifndef AGENCIA_H_
#define AGENCIA_H_

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Cliente;

class Conta { // @suppress("Class has a virtual method and non-virtual destructor")
protected:
  int numConta;
  float saldo;
  int numTransacoes;
  Cliente *titular2;
public:
	Conta(int nConta, float sd=0, int nTrans=0);
	int getNumConta() const;
	float getSaldo() const;
	int getNumTransacoes() const;
	Cliente *getTitular2() const;
	void setTitular2(Cliente *cli2);
	void deposito(float valor);
	virtual bool levantamento(float valor);
};

class Normal: public Conta { // @suppress("Class has a virtual method and non-virtual destructor")
public:
   Normal(int nConta, float sd=0, int nTrans=0);
};


class DeOperacao: public Conta { // @suppress("Class has a virtual method and non-virtual destructor")
  float taxa;
public:
  DeOperacao(int nConta, float tx, float sd=0, int nTrans=0);
  bool levantamento(float valor);
};


class Cliente {
  string nome;
  vector<Conta *> contas;
public:
  Cliente(string nm);
  string getNome() const;
  vector<Conta *> getContas() const;
  void adicionaConta(Conta *c1);

};


class Gerente {
  int ID;
  string nome;
  vector<Cliente *> meusClientes;
public:
  static int nextID;
  Gerente(string nm);
  int getID() const;
  string getNome() const;
  void setGerenteID (int IDinicio);
};


class Agencia {
  string designacao;
  vector<Cliente *> clientes;
  vector<Gerente> gerentes;
public:
  Agencia(string desig);
  string getDesignacao() const;
  vector<Cliente *> getClientes() const;
  vector<Gerente> getGerentes() const;
  void adicionaCliente(Cliente *cli1);
  Conta *levantamento(string nomeCli, float valor);
  float fimMes() const;
  vector<Conta*> removeCliente(string nomeCli);
  bool operator< (const Agencia &a1);
  float operator()(const string &nome);
  void adicionaGerente(string nomeGer);
  void setGerenteID (int IDinicio);
};



#endif /* AGENCIA_H_ */
