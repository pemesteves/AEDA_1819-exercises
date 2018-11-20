/*
 * Supermercado.cpp
 *
 * Created on: Dec 3, 2014
 *
 */

#include "Supermercado.h"
#include <map>
#include <utility>
#include <sstream>

int Cliente::numeroItens() const{
	int num = 0;
	for(list<Cesto>::const_iterator it = cestos.begin(); it != cestos.end(); it++){
		num += it->getItens().size();
	}
	return num;
}

int Cliente::valorItens() const{
	int valor = 0;
	stack<Item> s;
	for(list<Cesto>::const_iterator it = cestos.begin(); it != cestos.end(); it++){
		if (!it->empty()){
			s = it->getItens();
			while(!s.empty()){
				valor += s.top().preco;
				s.pop();
			}
		}
	}
	return valor;
}

int Cliente::trocarItem(Item& novoItem){
	int numItens = 0;
	stack<Item> s;
	for(list<Cesto>::iterator it = cestos.begin(); it != cestos.end(); it++){
		if (!it->empty()){
			s = it->getItens();
			while(!it->empty()){
				it->popItem();
			}
			while(!s.empty()){
				if(s.top().produto == novoItem.produto && s.top().preco > novoItem.preco){
					numItens++;
					s.pop();
					it->pushItem(novoItem);
				}
				else{
					it->pushItem(s.top());
					s.pop();
				}
			}
		}
	}
	return numItens;
}

void Cliente::organizarCestos(){
	stack<Item> itens;
	vector<Item> v;
	for(list<Cesto>::iterator it = cestos.begin(); it != cestos.end(); it++){
		v.clear();
		itens = it->getItens();
		while(!itens.empty()){
			v.push_back(itens.top());
			itens.pop();
			it->popItem();
		}
		sort(v.begin(),v.end());
		for(vector<Item>::iterator it1 = v.begin(); it1 != v.end(); it1++){
			it->pushItem(*it1);
		}
	}
}

vector<string> Cliente::contarItensPorTipo(){
	map<string, int> m;
	map<string, int>::iterator im;
	pair<string, int> p;
	stack<Item> s;
	for(list<Cesto>::iterator it = cestos.begin(); it != cestos.end(); it++){
		if (!it->empty()){
			s = it->getItens();
			while(!s.empty()){
				im = m.find(s.top().tipo);
				if (im == m.end()){
					p = make_pair(s.top().tipo, 1);
					m.insert(p);
				}
				else{
					(*im).second++;
				}
				s.pop();
			}
		}
	}
	vector<string> v;
	ostringstream oss;
	for(im = m.begin(); im != m.end(); im++){
		oss.str(std::string());
		oss << (*im).first << " " << (*im).second;
		v.push_back(oss.str());
	}
	return v;
}

