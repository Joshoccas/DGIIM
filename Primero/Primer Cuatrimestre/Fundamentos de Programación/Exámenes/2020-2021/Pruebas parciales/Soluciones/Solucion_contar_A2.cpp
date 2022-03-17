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

enum class Tipo  {MuyCorta, Corta, Otra};		
	
/***************************************************************************/
/***************************************************************************/

Tipo Clasifica (string palabra)
{
	Tipo tipo; 
	
	if (palabra.length()==1 || palabra.length()==2) tipo = Tipo::MuyCorta;
	else if (palabra.length()<5) tipo = Tipo::Corta;
	else tipo = Tipo::Otra;		
	
	return (tipo);
}

/***************************************************************************/
/***************************************************************************/

string ToUpper(string palabra) {
	
	string cad_nueva; 
	 
	for (int i=0; i<palabra.length(); i++)
		cad_nueva += toupper(palabra.at(i));
		
	return (cad_nueva); 
}

/***************************************************************************/
/***************************************************************************/

int main()
{
	const string TERMINADOR = "FIN";

	struct RegContadores {		
		int muy_cortas;
		int cortas;
		int otras;
	};
	
	RegContadores cont = {0, 0, 0}; 
	
	string cad_final;	
	string palabra;
	
	int total = 0;	

	// Entradas y cálculos
	
	cin >> palabra; 

	while (palabra != TERMINADOR) {
				
		Tipo categoria_palabra = Clasifica(palabra); 
		
		switch (categoria_palabra) {
						
			case (Tipo::MuyCorta) :  	
				cont.muy_cortas++;
				break; 
			case (Tipo::Corta) :  	
				cont.cortas++;
				break; 				
			case (Tipo::Otra) :  	
				cont.otras++;
				break; 											
		};
		
		total++; 
		
		if (categoria_palabra==Tipo::Otra)
			cad_final += ToUpper(palabra); 
		else 
			cad_final += palabra; 
			
		cad_final += " "; 
		
		cin >> palabra;
	}

	// Salida
	
	cout << endl;	
	cout << cad_final << endl; 
	cout << endl;
	
	 
	cout << endl;
	cout << "Hay un total de " << total << " palabras." << endl;	
	cout << endl;
	cout << "Hay " << setw(2) << cont.muy_cortas << " muy cortas." << endl;	
	cout << "Hay " << setw(2) << cont.cortas     << " cortas." << endl;
	cout << "Hay " << setw(2) << cont.otras  << " otras." << endl;
	cout << endl;

	return 0;	
}

/***************************************************************************/
/***************************************************************************/
