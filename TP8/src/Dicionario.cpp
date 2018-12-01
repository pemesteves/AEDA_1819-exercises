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
	PalavraSignificado p(palavra, ""), p1("", "");
	if((p1 = palavras.find(p)) == p ){
		throw PalavraNaoExiste();
	}

	return p1.getSignificado();
}


bool Dicionario::corrige(string palavra, string significado)
{
	// a alterer
	return true;
}

void Dicionario::imprime() const
{
	palavras.printTree();
}
