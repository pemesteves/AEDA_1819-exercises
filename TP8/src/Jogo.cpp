#include "Jogo.h"
#include <sstream>

BinaryTree<Circulo> & Jogo::getJogo() {
	return jogo;
}


ostream &operator << (ostream &os, Circulo &c1)
{
	os << c1.getPontuacao() << "-";
	if(c1.getEstado())
		os << "true";
	else
		os << "false";
	os << "-" << c1.getNVisitas();
	return os;
}

BinaryTree<Circulo> Jogo::iniciaJogo(int pos,int niv, vector<int> &pontos, vector<bool> &estados)
{
	Circulo c1(pontos[pos],estados[pos]);
	if (niv==0)
		return BinaryTree<Circulo>(c1);
	BinaryTree<Circulo> filhoEsq = iniciaJogo(2*pos+1,niv-1,pontos, estados);
	BinaryTree<Circulo> filhoDir = iniciaJogo(2*pos+2,niv-1,pontos, estados);
	return BinaryTree<Circulo>(c1, filhoEsq, filhoDir);
}

Jogo::Jogo(int niv, vector<int> &pontos, vector<bool> &estados)
{
	jogo = iniciaJogo(0, niv, pontos, estados);
}


string Jogo::escreveJogo()
{
	BTItrLevel<Circulo> it(jogo);

	ostringstream oss;

	while(!it.isAtEnd()){
		oss << it.retrieve() << endl;
		it.advance();
	}

	return oss.str();
}


int Jogo::jogada()
{
	BTItrLevel<Circulo> it(jogo);
	int pos = 1;
	int pontos = -1;
	if(it.isAtEnd())
		return pontos;

	while(true){
		Circulo &c1 = it.retrieve();
		bool estado = c1.getEstado();
		int n;
		if(!estado)
			n = pos;
		else
			n = pos+1;
		c1.mudaEstado();
		c1.incNVisitas();
		pontos = c1.getPontuacao();
		int i = 0;
		while(i < n && !it.isAtEnd()){
			it.advance();
			i++;
		}
		if(!it.isAtEnd())
			pos += n;
		else
			break;
	}
	return pontos;
}



int Jogo::maisVisitado()
{
	BTItrLevel<Circulo> it(jogo);
	if(it.isAtEnd())
		return -1;
	int numVisitas = -1;
	it.advance();
	while(!it.isAtEnd()){
		if(it.retrieve().getNVisitas() > numVisitas){
			numVisitas = it.retrieve().getNVisitas();
		}
		it.advance();
	}

	return numVisitas;
}




