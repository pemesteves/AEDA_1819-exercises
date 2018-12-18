#include <iostream>
#include <string>
#include <fstream>
#include "Dicionario.h"
#include "BST.h"

using namespace std;


BST<PalavraSignificado> Dicionario::getPalavras() const
{ return palavras; }



bool PalavraSignificado::operator < (const PalavraSignificado &ps1) const
{
	return palavra < ps1.getPalavra();
}

ostream& operator<<(ostream & out, const PalavraSignificado &ps){
	out << ps.getPalavra() << endl << ps.getSignificado()<< endl;
	return out;
}


void Dicionario::lerDicionario(ifstream &fich)
{
	string word, significado;
	while(!fich.eof()){
		getline(fich, word);
		getline(fich, significado);
		PalavraSignificado p(word, significado);
		palavras.insert(p);
	}
}


string Dicionario::consulta(string palavra) const
{
	PalavraSignificado p(palavra, "");
	PalavraSignificado p1 = palavras.find(p);
	PalavraSignificado notFound("", "");

	if(p1 == notFound){
		BSTItrIn<PalavraSignificado> it(palavras);
		string pAnt = "", sAnt = "";
		while(!it.isAtEnd() && it.retrieve()<p){
			pAnt = it.retrieve().getPalavra();
			sAnt = it.retrieve().getSignificado();
			it.advance();
		}
		string pAp = "", sAp = "";
		if(!it.isAtEnd()){
			pAp = it.retrieve().getPalavra();
			sAp = it.retrieve().getSignificado();
		}
		throw PalavraNaoExiste(pAnt, sAnt, pAp, sAp);
	}

	return p1.getSignificado();
}


bool Dicionario::corrige(string palavra, string significado)
{
	PalavraSignificado p = palavras.find(PalavraSignificado(palavra, ""));
	if(p == PalavraSignificado("", "")){
		palavras.insert(PalavraSignificado(palavra, significado));
		return false;
	}
	else{
		palavras.remove(PalavraSignificado(palavra, ""));
		p.setSignificado(significado);
		palavras.insert(p);
		return true;
	}
}

void Dicionario::imprime() const
{
	palavras.printTree();
}
