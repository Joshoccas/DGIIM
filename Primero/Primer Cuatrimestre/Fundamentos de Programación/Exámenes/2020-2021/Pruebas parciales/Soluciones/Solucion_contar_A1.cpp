/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
/***************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


/***************************************************************************/
/***************************************************************************/

enum class Tipo  {Vocal, Consonante, Digito, Otro};		
	
/***************************************************************************/
/***************************************************************************/
bool EsLetra (char c) 
{
	bool es_letra = false; 
	char c_may = toupper(c);
	
	if (c_may>='A' && c_may<='Z')
		es_letra = true;
		
	return (es_letra);		
}

/***************************************************************************/
/***************************************************************************/
bool EsVocal (char c) 
{
	bool es_vocal = false; 
	char c_may = toupper(c);
	
	if (c_may=='A' || c_may=='E' || c_may=='I'|| c_may=='O'|| c_may=='U')
		es_vocal = true;
		
	return (es_vocal);	
}

/***************************************************************************/
/***************************************************************************/

bool EsConsonante (char c) 
{
	return (EsLetra(c) && !EsVocal(c));
}

/***************************************************************************/
/***************************************************************************/

bool EsDigito (char c) 
{
	return (c>='0' && c<='9');
}

/***************************************************************************/
/***************************************************************************/


bool EsOtro (char c) 
{
	return (!EsLetra(c) && !EsDigito(c));
}

/***************************************************************************/
/***************************************************************************/

Tipo Clasifica (char letra)
{
	Tipo tipo; 
	
	if (EsVocal(letra))  tipo = Tipo::Vocal;
	else if (EsConsonante(letra)) tipo = Tipo::Consonante;
	else if (EsDigito(letra)) tipo = Tipo::Digito;
	else tipo = Tipo::Otro;		
	
	return (tipo);
}


/***************************************************************************/
/***************************************************************************/

int main()
{
	
	struct RegContadores {		
		int num_vocales;
		int num_cons;	 
		int num_digitos;
		int num_otros;		 
	};
	
	RegContadores contadores = {0, 0, 0, 0}; 
	
	
	const char TERMINADOR = '#';
	
	char c; 
	
	int total = 0;	

	// Entradas y cálculos
	
	cin >> c; 

	while (c != '#') {
		
		Tipo categoria_c = Clasifica(c); 
		
		switch (categoria_c) {
			
			case (Tipo::Vocal) :  	
				contadores.num_vocales++;
				break; 
			case (Tipo::Consonante) :  	
				contadores.num_cons++;
				break; 				
			case (Tipo::Digito) :  	
				contadores.num_digitos++;
				break; 				
			case (Tipo::Otro) :  	
				contadores.num_otros++;
				break; 									
		};
		total ++; 
		
		cin >> c;
	}
	
	// Salida
	 
	cout << endl;
	cout << "Hay un total de " << total << " caracteres." << endl;	
	cout << endl;
	cout << "Hay " <<setw(2) << contadores.num_vocales << " vocales." << endl;	
	cout << "Hay " <<setw(2) << contadores.num_cons << " consonantes." << endl;
	cout << "Hay " <<setw(2) << contadores.num_digitos << " digitos." << endl;
	cout << "Hay " <<setw(2) << contadores.num_otros << " otros." << endl;	
	cout << endl;

	return 0;	
}

/***************************************************************************/
/***************************************************************************/
