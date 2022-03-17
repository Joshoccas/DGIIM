/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// PRUEBA 02 - TIPO B
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

	const int NUM_FILAS = 10;  // Núm. filas de la matriz
	const int NUM_COLS  = 10;  // Núm. filas de la matriz
	const int NUM_CASILLAS = NUM_FILAS*NUM_COLS;
	
	// Para generar números aleatorios entre MIN_VALOR y MAX_VALOR
	const int MIN_VALOR = 4;   // Mínimo valor posible
	const int MAX_VALOR = 10;  // Máximo valor posible
	const int NUM_VALORES = MAX_VALOR-MIN_VALOR+1; // Número de valores 

	// Para la presentación de datos
	const int NUM_DATOS_LINEA = 10; 
	
	// Matriz de trabajo
	int m[NUM_FILAS][NUM_COLS] = {0};

	// Contadores 
	// las veces que aparece el valor "x" (MIN_VALOR <= x <= MAX_VALOR) 
	// en la matriz "m" se apunta en la casilla x-MIN_VALOR
	int veces[NUM_VALORES] = {0};


	// Inicializa el generador de números aleatorios con el reloj del 
	// sistema  (hora actual)
	time_t t;
	srand ((int) time(&t)); 
	
	
	cout << "Generando numeros entre " << setw(3) << MIN_VALOR
	     << " y " << MAX_VALOR << endl; 
	
	// Rellenar la matriz con valores aleatorios entre MIN_VALOR y MAX_VALOR
	
	for (int f=0; f< NUM_FILAS; f++) 
		for (int c=0; c< NUM_COLS; c++) 
			m[f][c] = (rand() % NUM_VALORES)+MIN_VALOR; 
			
	cout << endl; 
	cout << "Matriz de valores: " << endl; 
	cout << endl; 
	
	for (int f=0; f< NUM_FILAS; f++) {
		
		for (int c=0; c< NUM_COLS; c++) {

			cout << setw(4) << m[f][c];
		}	
		cout << endl; 
	}



	// Calcular veces que aparece cada valor  
	
	for (int f=0; f< NUM_FILAS; f++) {
		
		for (int c=0; c< NUM_COLS; c++) {

			int valor = m[f][c];
			veces[valor-MIN_VALOR]++; 
		}	
	}
	
	
	// Comprobar integridad
	 
	int suma = 0; 
	for (int valor=MIN_VALOR; valor<=MAX_VALOR; valor++) 
		suma += veces[valor-MIN_VALOR]; 

	cout << endl; 
	if (suma == NUM_CASILLAS) 
		cout << "Integridad verificada." << endl;
	else 
		cout << "ERROR: Problema de integridad." << endl;		
	cout << endl; 


	// Resumen de apariciones

	cout << endl; 
	cout << "Repeticiones: " << endl; 
	cout << endl; 

	for (int valor=MIN_VALOR; valor<=MAX_VALOR; valor++) {
		
		int veces_aparece = veces[valor-MIN_VALOR];
		double proporcion = ((double)veces_aparece) / NUM_CASILLAS;
		double porcentaje = proporcion*100.0;
		
		cout << setw(3) << valor << ":" 
		     << setw(5) << veces_aparece
			 << setw(6) << setprecision(2) << porcentaje << " %" << endl; 		
	}	
	cout << endl; 

	return 0;	
}

/***************************************************************************/
/***************************************************************************/
