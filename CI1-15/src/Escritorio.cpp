#include "Escritorio.h"
#include <iostream>


//Documento
Documento::Documento(int nPag, float pP, float pA):
			numPaginas(nPag), pPreto(pP), pAmarelo(pA)
{ }
Documento::~Documento() {}

int Documento::getNumPaginas() const { return numPaginas; }

float Documento::getPercentagemPreto() const { return pPreto; }

float Documento::getPercentagemAmarelo() const { return pAmarelo; }

Documento Documento::operator+(Documento &d){
	int nPag = numPaginas + d.getNumPaginas();
	float percPreto = (pPreto*numPaginas + d.getPercentagemPreto()*d.getNumPaginas())/nPag;
	float percAmarelo = (pAmarelo*numPaginas + d.getPercentagemAmarelo()*d.getNumPaginas())/nPag;
	Documento d1(nPag, percPreto, percAmarelo);
	return d1;
}



//Impressora
Impressora::Impressora(string cod, int a): codigo(cod), ano(a)
{}
Impressora::~Impressora() {}

string Impressora::getCodigo() const
{ return codigo; }

int Impressora::getAno() const
{ return ano; }

vector<Documento> Impressora::getDocumentosImpressos() const
{ return docsImpressos; }

bool Impressora::imprime(Documento doc1){
	docsImpressos.push_back(doc1);
	return true;
}


//ImpressoraPB
ImpressoraPB::ImpressoraPB(string cod, int a, int toner): Impressora(cod, a), numPagImprimir(toner)
{}

int ImpressoraPB::getNumPaginasImprimir() const
{ return numPagImprimir; }

bool ImpressoraPB::imprime(Documento doc1){
	if (numPagImprimir-doc1.getNumPaginas() >= 0){
		Impressora::imprime(doc1);
		numPagImprimir -= doc1.getNumPaginas();
		return true;
	}
	return false;
}

bool ImpressoraPB::tonerBaixo() const{
	if (numPagImprimir < 30)
		return true;
	return false;
}


//ImpressoraCores
ImpressoraCores::ImpressoraCores(string cod, int a, int toner): Impressora(cod, a),
		numPagImprimirPreto(toner), numPagImprimirAmarelo(toner)
{}

int ImpressoraCores::getNumPaginasImprimir() const {
	if (numPagImprimirPreto < numPagImprimirAmarelo)
		return (int)numPagImprimirPreto;
	return (int)numPagImprimirAmarelo;
}

bool ImpressoraCores::imprime(Documento doc1){
	if (numPagImprimirAmarelo - doc1.getNumPaginas()*doc1.getPercentagemAmarelo()>=0 && numPagImprimirPreto - doc1.getNumPaginas()*doc1.getPercentagemPreto() >=0){
		Impressora::imprime(doc1);
		numPagImprimirAmarelo -= doc1.getNumPaginas()*doc1.getPercentagemAmarelo();
		numPagImprimirPreto -= doc1.getNumPaginas()*doc1.getPercentagemPreto();
		return true;
	}
	return false;
}

bool ImpressoraCores::tonerBaixo() const{
	if (numPagImprimirPreto < 20 || numPagImprimirAmarelo < 20)
		return true;
	return false;
}

//Funcionario
Funcionario::Funcionario(string cod): codigo(cod)
{}
Funcionario::~Funcionario() {}

void Funcionario::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

vector<Impressora *> Funcionario::getImpressoras() const
{ return impressoras; }

string Funcionario::getCodigo() const
{ return codigo; }



//Escritorio
Escritorio::Escritorio() {}
Escritorio::~Escritorio() {}

void Escritorio::adicionaImpressora(Impressora *i1)
{ impressoras.push_back(i1); }

void Escritorio::adicionaFuncionario(Funcionario f1)
{ funcionarios.push_back(f1); }

vector<Impressora *> Escritorio::getImpressoras() const
{ return impressoras; }

int Escritorio::numImpressorasSemResponsavel() const{
	vector<Impressora *> v, funcV;
	for (size_t i = 0; i < funcionarios.size(); i++){
		funcV= funcionarios[i].getImpressoras();
		for (size_t j = 0; j < funcV.size(); j++)
			v.push_back(funcV[j]);
	}
	int numImp = 0; bool found;
	for (size_t i = 0; i < impressoras.size(); i++){
		found = false;
		for (size_t j = 0; j < v.size(); j++){
			if (impressoras[i]->getCodigo() == v[j]->getCodigo() && impressoras[i]->getAno() == v[j]->getAno()){
				found = true;
				break;
			}
		}
		if (!found)
			numImp++;
	}
	return numImp;
}

vector<Impressora *> Escritorio::retiraImpressoras(int ano1){
	vector<Impressora *>::iterator it;
	vector<Impressora *> v;
	for (it = impressoras.begin(); it != impressoras.end(); it++){
		if ((*it)->getAno()<ano1){
			v.push_back((*it));
			impressoras.erase(it);
			it--;
		}
	}
	return v;
}

Impressora* Escritorio::imprimeDoc(Documento doc1) const{
	vector<Impressora *>::const_iterator it;
	for (it = impressoras.begin(); it != impressoras.end(); it++){
		if ((*it)->imprime(doc1)){
			return (*it);
		}
	}
	Impressora* x = new Impressora("inexistente", 0);
	return x;
}

vector<Impressora *> Escritorio::tonerBaixo() const{
	vector<Impressora *> v;
	vector<Impressora *>::const_iterator it = impressoras.begin();
	for (; it!=impressoras.end(); it++){
		if ((*it)->tonerBaixo())
			v.push_back(*it);
	}

	return v;
}

string Escritorio::operator()(const string &cod){
	vector<Impressora *> v;
	for (size_t i = 0; i < funcionarios.size(); i++){
		v = funcionarios[i].getImpressoras();
		for (size_t j = 0; j < v.size(); j++){
			if (v[j]->getCodigo() == cod)
				return funcionarios[i].getCodigo();
		}
	}
	return "nulo";
}

