/***************************************************************************/
// FUNDAMENTOS DE PROGRAMACIÓN
//
// (C) FRANCISCO JOSÉ CORTIJO BON
// DEPARTAMENTO DE CIENCIAS DE LA COMPUTACIÓN E INTELIGENCIA ARTIFICIAL
//
// RELACIÓN DE PROBLEMAS 6
//
/*	
	Programa que lee las coordenadas que definen un rectángulo y calcula una 
	serie de circunferencias centradas en el punto de corte de sus diagonales.
	Solo nos interesan aquellas que estén inscritas en el rectángulo.  	
	Guarda estas circunferencias en una colección.
*/
/***************************************************************************/

#include <iostream>
#include <iomanip>
#include <cctype>
#include <cmath>
#include <cstdlib>

using namespace std;

/***************************************************************************/
/***************************************************************************/

const double PRECISION_SON_IGUALES = 1e-6; // 0.000001
const double PI = 3.141592653589793;

/***************************************************************************/
/***************************************************************************/
// Función global (asociada a la constante PRECISION_SON_IGUALES) que
// permite que dos números reales muy próximos sean considerados iguales.

bool SonIguales(double uno, double otro) 
{
	return (fabs(uno-otro) <= PRECISION_SON_IGUALES);
}

/***************************************************************************/

////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// La clase "Punto2D" representa un punto en R^2  

class Punto2D
{
private:
	
	// La pareja (x,y) son las coordenadas de un punto en un espacio 2D
	double x;
	double y;

public:
	
	/***********************************************************************/
	// Constructor sin  argumentos
	// Es necesario para almacenar objetos "Punto2D" en un array o 
	// para ser un dato miembro de otra clase
	
	Punto2D (void) { }

	/***********************************************************************/
	// Constructor con argumentos.
	//
	// Recibe: abscisaPunto y ordenadaPunto, la abscisa y ordenada, 
	// respectivamente del punto que se está creando.
	
	Punto2D (double abscisaPunto, double ordenadaPunto)
	{
		SetCoordenadas (abscisaPunto, ordenadaPunto);
	}

	/***********************************************************************/
	// Método Set para fijar simultaneamente las coordenadas. 
	//
	// Recibe: abscisaPunto y ordenadaPunto, la abscisa y ordenada, 
	// respectivamente del punto que se está modificando.
	
	void SetCoordenadas (double abscisaPunto, double ordenadaPunto)
	{
		x = abscisaPunto;
		y = ordenadaPunto;
	}

	/***********************************************************************/
	// Métodos Get para leer las coordenadas

	double GetX (void) { return (x); }
	double GetY (void) { return (y); }

	/***********************************************************************/
	// Calcula si dos puntos son iguales 
	//
	// Recibe: otro, el punto que se quiere comparar con el objeto implícito. 
	// Devuelve: true, si se consideran iguales los dos objetos. 

	bool EsIgual (Punto2D otro)
	{
		return (SonIguales(x,otro.x) && SonIguales(y,otro.y));
	}

	/***********************************************************************/
	// Calcula la distancia Euclídea del punto (objeto implícito) a otro que 
	// se recibe como argumento. 
	//
	// Recibe: otro, el punto respecto al cual que se quiere calcular la 
	// distancia euclídea.
	// Devuelve: la distancia entre los dos puntos. 

	double DistanciaEuclidea (Punto2D otro)
	{
		double dif_x = pow (x - otro.x, 2);
		double dif_y = pow (y - otro.y, 2);

		return (sqrt(dif_x + dif_y));
	}

	/***********************************************************************/
	// Devuelve la representación en una cadena de un punto
	string ToString (void)
	{
		string cad;
		cad = "[ " + to_string (x) + ", " + to_string (y) + "]";	
		return (cad);
	}

	/***********************************************************************/
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// La clase "Circunferencia" representa circunferencias, objetos geométricos 
// que verifican la propiedad de que los puntos (x,y) que la forman están a 
// la misma distancia de otro punto (el centro).

class Circunferencia
{
private:

	// La constante "PI" es común a todos los objetos de la clase.
	static const double PI;		
	
	// Centro de la circunferencia
	Punto2D centro;	
	
	// Longitud del radio
	// PRE: radio >= 0
	double  radio;	

public:

	/***********************************************************************/
	// Constructor sin  argumentos
	// Es necesario para almacenar objetos "Circunferencia" en un array o 
	// para ser un dato miembro de otra clase
	// Observad cómo se ha iniciado "centro": como es de clase "Punto2D"
	// se ha empleado la lista de iniciación para que actúe el constructor
	// de la clase "Punto2D" 
	
	Circunferencia (void) : centro(Punto2D()) { }

	/***********************************************************************/
	// Constructor con argumentos
	// Recibe:
	//		el_centro, el punto central de la circunferencia. 
	//		radio, el valor del radio.
	// PRE: radio >= 0
	// Observad cómo se ha iniciado "centro": como es de clase "Punto2D"
	// se ha empleado la lista de iniciación para que actúe el constructor
	// de la clase "Punto2D" 
	
	Circunferencia (Punto2D el_centro, double el_radio) 
	    : centro (el_centro), radio(el_radio) 
	{ }

	/***********************************************************************/
	// Métodos Get
	
	// Devuelve el punto central de la circunferencia
	Punto2D GetCentro (void) { return (centro); }

	// Devuelve el radio de la circunferencia
	double GetRadio (void) { return (radio); }

	// Devuelve el diámetro de la circunferencia
	double GetDiametro (void) { return (radio*2); }

	/***********************************************************************/
	// Calcula la longitud de la circunferencia

	double Longitud (void)
	{
		return (2.0 * PI * radio);
	}

	/***********************************************************************/
	// Calcula el área del círculo
	
	double Area (void)
	{
		return (PI * radio * radio);
	}

	/***********************************************************************/
	// Calcular si la circunferencia contiene a un punto dado usando un 
	// test explícito sobre la distancia Euclídea del centro de la 
	// circunferencia al punto.
	//
	// Recibe: un_punto, el punto del que se quiere evaluar su pertenencia. 
	/*
		Un punto P(x, y) está dentro de una circunferencia con centro 
		C(x_0, y_0) y radio r si DistaciaEuclidea (P, C) <= r
	*/
	// Esta implementación es preferible a la anterior ya que no requiere 
	// duplicar (aunque sea de manera indiirecta) el código referido al 
	// cálculo de la distancia entre dos puntos. 
	
	bool Contiene (Punto2D un_punto)
	{
		Punto2D el_centro = GetCentro();
		double distancia = el_centro.DistanciaEuclidea (un_punto);
		return (distancia <= radio);
	}

	/***********************************************************************/
	// Devuelve una cadena que representa a una Circunferencia
	
	string ToString (void)
	{
		string cad;
		cad = cad + "{" + centro.ToString() + ", " + to_string(radio) + "}";    
		return (cad);
	}
	
	/***********************************************************************/
};

const double Circunferencia :: PI = PI;

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// La clase "Rectangulo" representa rectángulos, paralelogramos que 
// verifican la propiedad de que los ángulos interiores son todos rectos. 
// Esta implementación considera únicamente rectángulos cuyos lados sean 
// paralelos a los ejes de coordenadas. 

class Rectangulo
{
private:

	// Esquina superior izquierda 
	Punto2D esquina_si;	
	
	// Longitud de los lados
	// PRE: long_ladoX, long_ladoY >= 0
	double long_ladoX; // Longitud de los lados paralelos al eje X
	double long_ladoY; // Longitud de los lados paralelos al eje Y	

public:

	/***********************************************************************/
	// Constructor con argumentos
	// Recibe:
	//		"la_esquina_si", el punto que determina la esquina superior izda.
	//		"la_long_ladoX", la longitud de los lados paralelos al eje X  
	//		"la_long_ladoY", la longitud de los lados paralelos al eje Y  
	// PRE: la_long_ladoX, la_long_ladoY >= 0

	Rectangulo (Punto2D la_esquina_si, double la_long_ladoX, 
	            double la_long_ladoY) : esquina_si (la_esquina_si) 
	{
		// Observad cómo se ha iniciado "esquina_si": como es de clase 
		// "Punto2D" se ha empleado la lista de iniciación para que actúe el 
		// constructor de la clase "Punto2D" 
		 
		long_ladoX  = la_long_ladoX; 
		long_ladoY  = la_long_ladoY; 
	}

	/***********************************************************************/
	// Métodos Get
	
	// Devuelve la esquina superior izquierda del rectángulo
	Punto2D GetEsquinaSI (void) { return (esquina_si); }
	
	// Devuelve la esquina superior derecha del rectángulo
	Punto2D GetEsquinaSD (void) 
	{
		return (Punto2D(esquina_si.GetX()+long_ladoX, esquina_si.GetY()));
	}
	// Devuelve la esquina inferior izquierda del rectángulo
	Punto2D GetEsquinaII (void) 
	{
		return (Punto2D(esquina_si.GetX(), esquina_si.GetY()-long_ladoY));
	}
	// Devuelve la esquina inferior derecha del rectángulo
	Punto2D GetEsquinaID (void)
	{
		return (Punto2D(esquina_si.GetX()+long_ladoX, 
		                esquina_si.GetY()-long_ladoY));
	}	
	
	// Devuelve la longitud del lado paralelo al eje X
	double GetLongitudLadoX (void) { return (long_ladoX); }
	
	// Devuelve la longitud del lado paralelo al eje Y
	double GetLongitudLadoY (void) { return (long_ladoY); }
	
	/***********************************************************************/
	// Calcula el área del rectángulo
	double Area (void)
	{
		return (long_ladoX*long_ladoY);
	}

	/***********************************************************************/
	// Calcula el perímetro del rectángulo	
	double Perimetro (void)
	{
		return (2*long_ladoX + 2*long_ladoY);
	}
	
	/***********************************************************************/
	// Calcula el punto central del rectángulo 
	Punto2D PuntoCentral (void)
	{
		double x = esquina_si.GetX() + (long_ladoX / 2);
		double y = esquina_si.GetY() - (long_ladoY / 2);
		
		return (Punto2D(x, y));
	}
		
	/***********************************************************************/
	// Calcula si el rectángulo contiene a un punto dado	
	bool Contiene (Punto2D un_punto)
	{
		return ((GetEsquinaSI().GetX() <= un_punto.GetX()) && 
		        (un_punto.GetX() <= GetEsquinaSD().GetX()) && 
			    (GetEsquinaSI().GetY() >= un_punto.GetY()) && 
		        (un_punto.GetY() >= GetEsquinaII().GetY()));
	}

	/***********************************************************************/
	// Devuelve una cadena que representa a un rectángulo
	string ToString (void)
	{
		string cad;
		cad = cad + GetEsquinaSI().ToString()+" - "+GetEsquinaSD().ToString() 
		      + " Long = " + to_string (long_ladoX) + "\n";
		cad = cad + GetEsquinaSD().ToString()+" - "+GetEsquinaID().ToString() 
		      + " Long = " + to_string (long_ladoY) + "\n";
		cad = cad + GetEsquinaID().ToString()+" - "+GetEsquinaII().ToString() 
		      + " Long = " + to_string (long_ladoX) + "\n";
		cad = cad + GetEsquinaII().ToString()+" - "+GetEsquinaSI().ToString() 
		      + " Long = " + to_string (long_ladoY) + "\n";    
		return (cad);
	}
	
	/***********************************************************************/
};

/////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// La clase "ColeccionCircunferencias" representa una secuencia de 
// datos "Circunferencia" 

class ColeccionCircunferencias 
{
private:

	// Datos asociados a la estructura de datos empleada para guardar 
	// los valores de la coleccion.

	static const int TAMANIO = 200; // Número de casillas disponibles

	Circunferencia vector_privado[TAMANIO];
	
	//PRE: 0 <= total_utilizados <= TAMANIO
	int total_utilizados;	// Número de casillas ocupadas
	
public:
	
	/***********************************************************************/
	// Constructor sin parámetros. 

	ColeccionCircunferencias (void) : total_utilizados(0) { }

	/***********************************************************************/
	// Constructor a partir de un punto. 
	//
	// Recibe: nueva, el único dato que forma la nueva colección. 
	
	ColeccionCircunferencias (Circunferencia nueva) : total_utilizados(0)
	{ 
		Aniade (nueva);
	}

	/***********************************************************************/
	// Métodos de lectura (Get) sobre tamaño y capacidad de la colección 

	// Devuelve el número de datos que componen la colección.
	int NumCircunferencias (void) { return (total_utilizados); }

	// Devuelve el número de datos que podrían formar una colección completa.
	int CapacidadColeccion(void) { return (TAMANIO); }

	/***********************************************************************/
	// Añade un dato a la colección.
	// Recibe: nueva, el dato que se va a añadir.
	//
	// PRE: total_utilizados < TAMANIO
	// 		La adición se realiza si hay espacio para el nuevo elemento. 
	// 		El nuevo elemento se coloca al final del vector. 
	// 		Si no hay espacio, no se hace nada.	

	void Aniade (Circunferencia nueva)
	{
		if (total_utilizados < TAMANIO) {
			vector_privado[total_utilizados] = nueva;
			total_utilizados++;
		}
	}

	/***********************************************************************/
	// Devuelve el elemento de la casilla "indice" 
	//
	// PRE: 0 <= indice < total_utilizados 

	Circunferencia Elemento (int indice)
	{
		return (vector_privado[indice]);
	}
		
	/***********************************************************************/
	// Deja la secuencia "vacía" 

	void EliminaTodos (void)
	{
		total_utilizados = 0;
	}

	/***********************************************************************/
	// Devuelve una cadena que representa una secuencia de "Circunferencia"
	string ToString (void)
	{
		string cad;
		
		for (int i=0; i<total_utilizados; i++) {
			
			cad = cad + vector_privado[i].ToString() + "\n";		
		} 
		return (cad);
	}
	
	/***********************************************************************/
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/***************************************************************************/
/***************************************************************************/

int main (void)
{
	cout.setf(ios::fixed);		// Notación de punto fijo para los reales
	cout.setf(ios::showpoint);	// Mostrar siempre decimales 
		
	const double RADIO_INIC = 0.5;  // Valor del radio inicial
	const double INCR_RADIO = 0.25;	// Incremento del valor del radio

	// Leer los valores que definen el rectángulo
	
	double x, y, ancho, alto; 

	cout << endl;
	cout << "Esquina sup. izda." << endl;
	cout << "\tx: ";
	cin >> x; 
	cout << "\ty: ";
	cin >> y;
		 	
	Punto2D esquina_si (x, y);

	cout << endl;
	cout << "Ancho: ";
	cin >> ancho;
	cout << "Alto: ";
	cin >> alto;

	// Crear el rectángulo
	
 	Rectangulo r (esquina_si, ancho, alto); 
 
	cout << endl;		
	cout << "Rectangulo = " << endl;	
	cout << endl; 
	cout << r.ToString() << endl;
	cout << endl; 
	
	// Calcular el centro del rectángulo
	
	Punto2D centro = r.PuntoCentral();
	
	cout << endl;		
	cout << "Punto central del rectangulo = " << centro.ToString ()<< endl;	
	cout << endl;		

	// Todas las circunferencias inscritas tendrán un radio menor o igual que 
	// la mitad de la longitud de la dimensión menor entre el alto y el ancho 
	// del rectángulo.

	double ancho_r = r.GetLongitudLadoX();
	double alto_r  = r.GetLongitudLadoY();
	double min_dimension = ((ancho_r < alto_r) ? ancho_r : alto_r);
	double max_radio = min_dimension / 2;	

	// Creamos una serie de circunferencias centradas en "centro", el centro 
	// del rectángulo. La primera tiene de radio RADIO_INIC. Para las sucesivas 
	// circunferencias sus radios se incrementan en INCR_RADIO. 

	ColeccionCircunferencias circ_inscritas;

	int cont = 0; 
	
	// El radio irá cambiando. El primer radio vale RADIO_INIC
	double radio = RADIO_INIC;
		
	while (radio <= max_radio) {
	
		Circunferencia c (centro, radio); 	// Crear circunferencia
		
		cont++; // Incrementar contador
		
		cout << "Guardando circunferencia " << setw(3) << cont 
		     << ": " << c.ToString () << endl;		

		circ_inscritas.Aniade(c); // Añadir a la colección
		
		radio += INCR_RADIO; // Incrementar radio
	} 
	
	// Integridad
	
	if (circ_inscritas.NumCircunferencias() != cont) {
		
		cout << endl; 
		cout << "Error de integridad."<< endl; 
		cout << endl; 		
		
		exit (1); 
	}

	// Mostrar datos de las circunferencias inscritas  

	cout << endl;
	cout << "Se han encontrado " <<circ_inscritas.NumCircunferencias() 
	     << " circunferencias inscritas:" << endl; 
	cout << endl;
	
	cout << circ_inscritas.ToString() << endl; 
	
	return 0;
}

/***************************************************************************/
/***************************************************************************/
