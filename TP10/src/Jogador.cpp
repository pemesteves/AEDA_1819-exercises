#include "Jogador.h"


void Jogador::adicionaAposta(const Aposta & ap)
{
	apostas.insert(ap);
}

unsigned Jogador::apostasNoNumero(unsigned num) const
{
	unsigned count = 0;
	for(tabHAposta::const_iterator it = apostas.begin(); it != apostas.end(); it++){
		if((*it).contem(num))
			count++;
	}
	return count;
}


tabHAposta Jogador::apostasPremiadas(const tabHInt & sorteio) const
{
	tabHAposta money;
	unsigned count = 0;
	for(tabHAposta::const_iterator it = apostas.begin(); it != apostas.end(); it++){
		count = 0;
		for(tabHInt::const_iterator it1 = sorteio.begin(); it1 != sorteio.end(); it1++){
			if((*it).contem(*it1))
				count++;
		}

		if(count > 3)
			money.insert(*it);
	}
	return money;
}
