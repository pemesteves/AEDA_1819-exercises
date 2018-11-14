#include <iostream>
#include <vector>

using namespace std;

/**
 * Versao da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
public:
	Grafo(){}
	~Grafo(){
		//Ou: typename vector<No<N,A>>::const_iterator it;...
		for (size_t i = 0; i < nos.size(); i++)
			delete nos.at(i);
	}
	Grafo & inserirNo(const N &dados);
	Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
	Grafo & eliminarAresta(const N &inicio, const N &fim);
	A & valorAresta(const N &inicio, const N &fim);
	int numArestas(void) const;
	int numNos(void) const{return (int)nos.size();}
	void imprimir(std::ostream &os) const;
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);


// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
	N info;
	NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }



// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};


//excecao ArestaRepetida
template <class N, class A>
class ArestaRepetida{
public:
	No<N,A> *dest;
	A val;
	ArestaRepetida(No<N,A> &fim, A &val){
		dest = fim;
		this->val = val;
	}
};


template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

template <class N, class A>
int Grafo<N,A>::numArestas(void) const{
	int arestas = 0;
	for (size_t i = 0; i < nos.size(); i++)
		arestas += nos[i]->arestas.size();
	return arestas;
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirNo(const N &dados){
	for (size_t i = 0; i < nos.size(); i++){
		if (dados == nos[i]->info){
			throw NoRepetido<N>(dados);
		}
	}

	No<N,A> *no = new No<N,A>(dados);
	nos.push_back(no);

	return *this;
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val){
	Grafo<N,A> *n = NULL;

	for (size_t i = 0; i < nos.size(); i++){
		if (nos[i]->info == inicio){
			if (nos[i]->arestas.destino->info == fim)
				throw ArestaRepetida<N,A>(fim, val);
			*n = nos[i];
			break;
		}
	}

	if (n == NULL)
		throw NoInexistente<N>(inicio);

	Aresta<N,A> a = new Aresta<N,A>(n, val);

	(*n)->nos.push_back(a);
}

