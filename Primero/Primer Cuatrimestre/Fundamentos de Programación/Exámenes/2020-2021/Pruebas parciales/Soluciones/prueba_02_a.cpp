/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// PRUEBA 02 - TIPO A
//
/***************************************************************************/

#include<iostream>
#include <iomanip>
#include <string>
#include<ctime>
#include<cstdlib>
#include<cctype>
using namespace std;
	
/***************************************************************************/
/***************************************************************************/

int main()
{		
	cout.setf(ios::showpoint);
	cout.setf(ios::fixed);
	
    //.......................................................................
	// Para generar números aleatorios

	const int NUM_FILAS = 5;  // Núm. valores posibles
	const int NUM_COLS  = 5;  // Núm. valores posibles
	
	const int NUM_VALORES = NUM_FILAS*NUM_COLS; 

	const int NUM_DATOS_LINEA = 10; 
	
	// Matriz de trabajo
	int m[NUM_FILAS][NUM_COLS] = {0};

	// Veces que se intenta alojar cada valor
	int veces[NUM_VALORES] = {0};


	// Inicializa el generador de números aleatorios con el reloj del 
	// sistema  (hora actual)
	time_t t;
	srand ((int) time(&t)); 
	

	int cont_total = 0; // Contador global				
	
	for (int valor = 1; valor <= NUM_VALORES; valor++) {

		int cont_valor  = 0;  // Intentos para colocar "valor"
		 
 		bool encontrado_sitio = false; 
		
		while (!encontrado_sitio) {
		
			cont_valor++;	
			
			// Calcular el número de fila y columna 
			
			// 0 <= fila < NUM_FILAS
		    int fila = rand() % NUM_FILAS; 
		    // 0 <= col < NUM_COLS
		    int col  = rand() % NUM_COLS; 
			 
			encontrado_sitio = (m[fila][col] == 0); 
			
			if (encontrado_sitio) m[fila][col] = valor;
		} 
					
		veces[valor-1] = cont_valor; 			
				
		cont_total += cont_valor;	
	}
				
	cout << endl; 
	cout << "Intentos para alojar los valores: " << endl; 
	cout << endl; 

	for (int pos=0; pos<NUM_VALORES; pos++) 
		cout << setw(5) << veces[pos] 
		     << (((pos+1)%NUM_DATOS_LINEA==0)?"\n":""); 		
	cout << endl; 

	double media = ((double)cont_total) / NUM_VALORES; 
	
	cout << endl; 
	cout << "Intentos totales  " << setw(5) << cont_total << endl; 
	cout << "Media: " << setw(6) << setprecision(2) << media << endl; 
	cout << endl; 

	
	cout << endl; 
	cout << "Matriz de valores: " << endl; 
	cout << endl; 
	
	for (int f=0; f< NUM_FILAS; f++) {
		
		for (int c=0; c< NUM_COLS; c++) {

			cout << setw(4) << m[f][c];
		}	
		cout << endl; 
	}

	return 0;	
}

/***************************************************************************/
/***************************************************************************/
