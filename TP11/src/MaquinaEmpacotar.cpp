/*
 * Empacotador.cpp
 */

#include "MaquinaEmpacotar.h"
#include <sstream>


MaquinaEmpacotar::MaquinaEmpacotar(int capCaixas): capacidadeCaixas(capCaixas)
{}

unsigned MaquinaEmpacotar::numCaixasUsadas() {
	return caixas.size();
}

unsigned MaquinaEmpacotar::addCaixa(Caixa& cx) {
	caixas.push(cx);
	return caixas.size();
}

HEAP_OBJS MaquinaEmpacotar::getObjetos() const {
	return this->objetos;
}

HEAP_CAIXAS MaquinaEmpacotar::getCaixas() const {
	return this->caixas;
}


/* a implementar pelos estudantes */

unsigned MaquinaEmpacotar::carregaPaletaObjetos(vector<Objeto> &objs) {
	unsigned num = 0;
	for(vector<Objeto>::iterator it = objs.begin(); it != objs.end(); it++){
		if((*it).getPeso() <= capacidadeCaixas){
			objetos.push(*it);
			it = objs.erase(it);
			it--;
			num++;
		}
	}
	return num;
}


Caixa MaquinaEmpacotar::procuraCaixa(Objeto& obj) {
	Caixa cx;
	HEAP_CAIXAS novasCaixas;
	bool foundBox = false;
	while(!caixas.empty()){
		if(!foundBox && caixas.top().getCargaLivre() >= obj.getPeso()){
			cx = caixas.top();
			caixas.pop();
			foundBox = true;
		}
		else{
			novasCaixas.push(caixas.top());
			caixas.pop();
		}
	}
	while(!novasCaixas.empty()){
		caixas.push(novasCaixas.top());
		novasCaixas.pop();
	}
	return cx;
}


unsigned MaquinaEmpacotar::empacotaObjetos() {
	vector<unsigned> ids;

	while(!objetos.empty()){
		Objeto obj = objetos.top();
		objetos.pop();
		Caixa cx = procuraCaixa(obj);
		cx.addObjeto(obj);
		caixas.push(cx);
		bool foundCaixa = false;
		for(vector<unsigned>::iterator it = ids.begin(); it != ids.end(); it++){
			if((*it) == cx.getID()){
				foundCaixa = true;
			}
		}
		if(!foundCaixa){
			ids.push_back(cx.getID());
		}
	}
	return ids.size();
}

string MaquinaEmpacotar::imprimeObjetosPorEmpacotar() const {
	if(objetos.size() == 0)
		return "Nao ha objetos!\n";

	HEAP_OBJS novosObjetos = objetos;

	ostringstream oss;
	while(!novosObjetos.empty()){
		oss << novosObjetos.top() << "\n";
		novosObjetos.pop();
	}
	return oss.str();
}



Caixa MaquinaEmpacotar::caixaMaisObjetos() const {
	if(caixas.size() == 0)
		throw MaquinaSemCaixas();
	HEAP_CAIXAS novasCaixas = caixas;
	Caixa cx = novasCaixas.top();
	novasCaixas.pop();
	while(!novasCaixas.empty()){
		if(cx.getSize() < novasCaixas.top().getSize())
			cx = novasCaixas.top();
		novasCaixas.pop();
	}
	return cx;
}



