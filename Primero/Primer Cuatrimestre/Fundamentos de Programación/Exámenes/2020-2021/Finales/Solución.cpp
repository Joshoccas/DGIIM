/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACI?N
//
// (C) FRANCISCO JOS? CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACI?N E INTELIGENCIA ARTIFICIAL
//
/***************************************************************************/

/***************************************************************************/
// EJERCICIO 1
/***************************************************************************/

// M?todos p?blicos de la clase SecuenciaCaracteres: 

/***********************************************************************/
// Devuelve una secuencia incluida en la secuencia impl?cita, que empieza 
// en la posici?n "inicio" y tiene "num" valores
//
// Recibe: inicio, posici?n inicial desde donde empieza la copia hacia 
//				   la subsecuencia. 
//		   num, n?mero de valores que se copian a la subsecuencia. 
// Devuelve: una subsecuencia de la secuencia impl?cita. 
// 
// Casos: 1) Si 0 <= inicio < total_utilizados Y 
//			 inicio+num<=total_utilizados
//			 se devuelve una subsecuencia de tama?o "num"
//		  2) Si 0 <= inicio < total_utilizados Y 
//			 inicio+num>total_utilizados, se devuelve una 
//			 subsecuencia de tama?o total_utilizados-inicio
//		  3) Si inicio < 0 ? inicio >= total_utilizados, 
//			 se devuelve una subsecuencia vac?a.
//		  4) Si num <= 0, se devuelve una subsecuencia vac?a.

SecuenciaCaracteres SubSecuencia (int inicio, int num)
{
	SecuenciaCaracteres a_devolver; // inicialmente vac?a
	
	if ((inicio>=0) && (inicio<total_utilizados) && (num>0)) {
		
		int fin;
		
		if (inicio+num>total_utilizados) 
			fin = total_utilizados;
		else 
			fin = inicio+num;
		
		for (int pos=inicio; pos<fin; pos++)
			a_devolver.Aniade(vector_privado[pos]);
	}
	
	return (a_devolver);
}

/***********************************************************************/
// Devuelve true si la secuencia es una palabra "seudosim?trica". 
// Una palabra "seudosim?trica" se define como una palabra que, cuando se 
// parte por la mitad, da como resultado dos palabras que tienen las 
// mismas letras con las mismas frecuencias. Si la longitud de la palabra 
// es un n?mero impar, la decisi?n se toma sin considerar la letra central.

bool EsSeudoSimetrica (void)
{
	// Cada una de las dos mitades ser? un dato "SecuenciaCaracteres"
	SecuenciaCaracteres SubSecuenciaIzda, SubSecuenciaDcha;
	
	int long_sec = TotalUtilizados(); 	// long. de la secuencia impl?cita.
	int long_sub = long_sec/2;			// long. de cada mitad
	
	// La mitad izquierda no requiere ninguna preacauci?n
	SubSecuenciaIzda = SubSecuencia(0, long_sub); 
	
	// La mitad derecha requiere atenci?n: hay que descartar el car?cter
	// que est? en la posici?n mediana si la longitud es impar, o sea 
	// empezar en la posici?n long_sub+1
	
	if (long_sec%2==0) SubSecuenciaDcha = SubSecuencia(long_sub,long_sub); 
	else SubSecuenciaDcha = SubSecuencia(long_sub+1,long_sub); 
	
	// Contar la frecuencia de aparici?n de los caracteres de cada mitad
	// Usamos dos arrays, uno por cada subsecuencia. Tendr?n tantas 
	// casillas como caracteres hay (NUM_LETRAS). En la casilla "i" se 
	// guarda el n?mero de apariciones del car?cter n?mero "i" ('a' y 'A' 
	// en la casilla 0, 'b' y 'B' en la casilla 1, 'c' y 'C' en la 2, ...)
	const int NUM_LETRAS = 'Z'-'A'+1; 
	int contadores_izda [NUM_LETRAS] = {0};
	int contadores_dcha [NUM_LETRAS] = {0};
	
	// Las dos subsecuencias miden lo mismo: "long_sub"
	// Actualizar contadores de las dos subsecuencias
	
	for (int pos=0; pos<long_sub; pos++) {
		
		char letra_izda = toupper(SubSecuenciaIzda.Elemento(pos));
		contadores_izda[letra_izda-'A']++;
		
		char letra_dcha = toupper(SubSecuenciaDcha.Elemento(pos));
		contadores_dcha[letra_dcha-'A']++;	
	}
	
	// Comparar los contadores de las dos secuencias. 
	// Terminar cuando se encuentre una discrepancia.
	 
	int pos=0; 
	bool es_seudosimetrica = true; 
	
	while (pos<NUM_LETRAS && es_seudosimetrica) {
		if (contadores_izda[pos] != contadores_dcha[pos]) 
			es_seudosimetrica = false;
		else pos++;
	}
	
	return (es_seudosimetrica);
}

/***********************************************************************/





/***************************************************************************/
// EJERCICIO 2
/***************************************************************************/


// M?todos p?blicos de la clase SecuenciaEnteros: 

/***********************************************************************/
// Calcula la suma de los elementos de la secuencia

int Suma (void)
{
	int suma = 0;

	for (int pos=0; pos<total_utilizados; pos++) 
		suma += vector_privado[pos];

	return (suma);
}

/***********************************************************************/


// M?todos p?blicos de la clase Tablero: 


/***********************************************************************/
// Devuelve la diagonal principal (0,0) a (dimension-1, dimension-1) 

SecuenciaEnteros DiagonalPrincipal (void)
{
	SecuenciaEnteros diagonal;
	
	for (int pos=0; pos<dimension; pos++)
		diagonal.Aniade(matriz_privada[pos][pos]);	

	return (diagonal);
}

/***********************************************************************/
// Devuelve la diagonal inversa (0,dimension-1) a (dimension-1, 0) 

SecuenciaEnteros DiagonalInversa (void)
{
	SecuenciaEnteros diagonal;
	
	for (int pos=0; pos<dimension; pos++)
		diagonal.Aniade(matriz_privada[pos][dimension-1-pos]);	
				
	return (diagonal);
}


/***********************************************************************/
// Devuelve true si la tabla es un cuadrado califragilistico.
// Si la tabla es cuadrada y sus dimensiones son n x n , se suman las 
// n filas, n columnas y 2 diagonales. Si todos los valores de las 
// 2*n + 2 sumas son diferentes es un cuadrado califragilistico.	

bool EsCalifragilistico (void)	
{			
	return (SumaTodas().TotalUtilizados() == (2*dimension)+2); 
}

/***********************************************************************/
// Devuelve true si la tabla es un cuadrado supercalifragilistico.
// Para que una tabla sea supercalifragilistico: 
//  1) debe ser califragilistico: si la tabla es cuadrada y sus dimensiones 
//		son n x n, se suman las n filas, n columnas y las dos diagonales. 
//		Si todos los valores de las 2*n+2 sumas son diferentes, es un 
//		cuadrado califragilistico. 	
// 2) los valores de las 2*n+2 sumas son consecutivos.

bool EsSuperCalifragilistico (void)
{	
	bool es_cuadrado_supecalifragilistico = true; 
		
	SecuenciaEnteros sumas = SumaTodas();
	int num_valores = sumas.TotalUtilizados();

	if (num_valores != (2*dimension)+2)
	
		es_cuadrado_supecalifragilistico = false; 
		
	else {
		
		// El tablero un cuarado califragilistico. La secuencia "sumas" 
		// tiene todos sus valores distintos, pero ?son consecutivos?
		// 
		// Si est?n presentes todos los valores entre el m?nimo y el 
		// m?ximo en "sumas", entonces es un cuadrado supercalifragilistico
		
		int minimo = sumas.Minimo (0, num_valores-1);
		int maximo = sumas.Maximo (0, num_valores-1);
		
		es_cuadrado_supecalifragilistico=((maximo-minimo)+1==num_valores);			
	}
	
	return (es_cuadrado_supecalifragilistico); 
  }

/***********************************************************************/



// M?todos privados de la clase Tablero: 

/***********************************************************************/
// Si la tabla es cuadrada y su dimensi?n es dxd, este m?todo devuelve 
// una secuencia que contiene, como m?ximo, 2*d+2 valores. 
// 
// Se construye a?adiendo la suma de cada fila (d valores), cada columna 
// (d valores) y las dos diagonales. Se van a?adiendo conforme se 
// calculan.
// - Si alguno de estos valores YA estuviera en la secuencia entonces 
//	 NO se a?ade y se termina el proceso. 	
// - Si la secuencia devuelta contiene exactamente 2*d+2 valores, 
// 	 entonces NO contiene valores repetidos.

SecuenciaEnteros SumaTodas() 
{
    SecuenciaEnteros sumas;
    
    int valor_suma;
    bool sigo = true;
	
    for (int i = 0; i < dimension && sigo; i++) {
    	
		valor_suma = Fila(i).Suma();

		// Si la suma de la fila "i" ya est?, terminar.
		// Si no, se a?ade el valor a la secuencia y seguir. 
      
		if (sumas.Existe(valor_suma, 0, sumas.TotalUtilizados()-1))  
			sigo = false;
			
		else {
			
			sumas.Aniade(valor_suma);

			valor_suma = Columna(i).Suma();
			
			// Si la suma de la columna "i" ya est?, terminar.
			// Si no, se a?ade el valor a la secuencia y seguir. 
			
			if (sumas.Existe(valor_suma, 0, sumas.TotalUtilizados()-1)) 
				sigo = false;
			else 
				sumas.Aniade(valor_suma);
		}
		
	} // for "i"
	
	if (sigo) {
      	
		// Comprobar diagonal principal
			
		valor_suma = DiagonalPrincipal().Suma();

		// Si la suma de la diagonal principal ya est?, terminar.
		// Si no, se a?ade el valor a la secuencia y seguir. 
			
		if (sumas.Existe(valor_suma, 0, sumas.TotalUtilizados()-1)) 

			sigo = false; 
					
		else  { // Comprobar diagonal inversa
		
			sumas.Aniade(valor_suma);

			valor_suma = DiagonalInversa().Suma();

			// Si la suma de la diagonal inversa ya est?, terminar.
			// Si no, se a?ade el valor a la secuencia. 
		
			if (sumas.Existe(valor_suma, 0, sumas.TotalUtilizados()-1))  
				sigo = false;
			else sumas.Aniade(valor_suma);
		}
	}	
	
	return sumas;
}

/***********************************************************************/
