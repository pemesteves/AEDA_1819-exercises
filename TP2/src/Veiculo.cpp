#include "Veiculo.h"
#include <iostream>

using namespace std;

Veiculo::Veiculo(string mc, int m, int a){
	marca = mc;
	mes = m;
	ano = a;
}

int Veiculo::info() const{
	cout << "Marca: " << marca << endl;
	cout << "Mes: " << mes << endl;
	cout << "Ano: " << ano << endl;
	return 3;
};

bool Veiculo::operator < (const Veiculo & v) const{
	if (ano < v.ano)
		return true;
	if (mes < v.mes)
		return true;

	return false;
};

Motorizado::Motorizado(string mc, int m, int a,string c,int cil):
										Veiculo(mc, m, a){
	combustivel = c;
	cilindrada = cil;
}

int Motorizado::info() const{
	int infoV = Veiculo::info();
	cout << "Combustivel: " << combustivel << endl;
	cout << "Cilindrada: " << cilindrada << endl;
	return infoV + 2;
}

float Motorizado::calcImposto() const{
	if ((combustivel == "gasolina" && cilindrada <= 1000)
			|| (combustivel != "gasolina" && cilindrada <= 1500)){
		if (ano > 1995)
			return 14.56;
		else
			return 8.1;
	}
	else if ((combustivel == "gasolina" && cilindrada > 1000 &&
			cilindrada <= 1300)|| (combustivel != "gasolina" &&
					cilindrada > 1500 && cilindrada <= 2000)){
		if (ano > 1995)
			return 29.06;
		else
			return 14.56;
	}
	else if ((combustivel == "gasolina" && cilindrada > 1300 &&
			cilindrada <= 1750)|| (combustivel != "gasolina" &&
					cilindrada > 2000 && cilindrada <= 3000)){
		if (ano > 1995)
			return 45.15;
		else
			return 22.65;
	}
	else if((combustivel == "gasolina" && cilindrada > 1750 &&
			cilindrada <= 2600)|| combustivel != "gasolina"){
		if (ano > 1995)
			return 113.98;
		else
			return 54.89;
	}
	else if (cilindrada > 2600 && cilindrada <= 3500){
		if (ano > 1995)
			return 182.17;
		else
			return 87.13;
	}
	else{
		if (ano > 1995)
			return 320.89;
		else
			return 148.37;
	}
}

Automovel::Automovel(string mc, int m, int a,string c, int cil):
										Motorizado(mc, m, a, c, cil){};

int Automovel::info() const{
	int infoM = Motorizado::info();
	return infoM;
}

Camiao::Camiao(string mc, int m, int a,string c, int cil,int cm):
										Motorizado(mc, m, a, c, cil){
	carga_maxima = cm;
}

int Camiao::info() const{
	int infoM = Motorizado::info();
	cout << "Carga Máxima: " << carga_maxima << endl;
	return infoM+1;
}

Bicicleta::Bicicleta(string mc, int m, int a,string t):
										Veiculo(mc, m, a){
	tipo = t;
}

int Bicicleta::info() const{
	cout << "Tipo: " << tipo << endl;
	return 1;
}

float Bicicleta::calcImposto() const{
	return 0;
}
