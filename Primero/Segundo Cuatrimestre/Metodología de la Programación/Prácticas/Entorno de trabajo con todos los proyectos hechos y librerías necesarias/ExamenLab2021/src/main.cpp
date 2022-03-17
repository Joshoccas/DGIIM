#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int nalumnos = 51;
const string _nombres[] = {"JOSE ALGAR FERNANDEZ", "JOAQUIN ARCILA PEREZ", "GERARDO ARENAS NASRAWIN", "CARMEN AZORIN MARTI", "RUBEN BALLESTEROS RIVERO", "MARTA BENITEZ HERNANDEZ", "MANUEL VICENTE BOLAÑOS QUESADA", "CLARA BOLIVAR PELAEZ", "LORENA CACERES ARIAS", "PEDRO HAIMAR CASTILLO GARCIA", "LUCIA CEPEDA GONZALEZ", "MARIA CRIBILLES PEREZ", "MANUEL DIAZ-MECO TERRES", "PABLO GALVEZ ORTIGOSA", "JESUS SAMUEL GARCIA CARBALLO", "CARLOS GARCIA JIMENEZ", "BORA GOKER SOLA", "JAVIER GOMEZ LOPEZ", "ANA GRACIANI DONAIRE", "JOSE ALBERTO HOCES CASTRO", "SHAO JIE HU CHEN", "ADRIAN JAEN FUENTES", "AARON JERONIMO FERNANDEZ", "NOURA LACHHAB BOUHMADI", "LAURA LAZARO SORALUCE", "RAMON LIRIA SANCHEZ", "ENRIQUE LOPEZ GARCIA", "CARLOTA LOPEZ QUESADA", "PAULA MANGANO GONZALEZ", "JOSE MARIA MARTIN MARTIN", "JAIME MARTINEZ BRAVO", "FRANCISCO NICOLAS MEDINA ROSAS", "MARIO MEGIAS MATEO", "JOSE LUIS MERA CARDOSO", "CRISTOBAL MERINO SAEZ", "QUINTIN MESA ROMERO", "ALVARO MOLINA ALVAREZ", "JUAN MOLINA MOLINA", "EDUARDO MOLINA VELAZQUEZ", "CLARA ORTEGA SEVILLA", "CARLOS MANUEL PERALES GOMEZ", "PEDRO PLAZAS MUNUERA", "CARLOS QUESADA PEREZ", "EDUARDO RODRIGUEZ CAO", "TOMAS RODRIGUEZ HERNAEZ", "ELSA RODRIGUEZ MACMICHAEL", "MARIO RUBIO VENZAL", "MANUEL RUIZ AGUILAR", "SOLEDAD RUIZ GOMEZ", "DAVID TORONJO MENDOZA", "ELENA TORRES FERNANDEZ"};

void Introduccion(const string &nombre){
    int _i, _tipo;
    string aux;
    cout << "Buscando (" << nombre << ")" << endl;
    for (_i = 1; _i <= nalumnos && _nombres[_i - 1] != nombre; _i++);
    if (_i <= nalumnos) {
        cerr << "Alumno: " << nombre << endl;
        cerr << "Fichero: " << "1." + to_string(_i) + ".xhtml" << endl;
        cerr << "Variante: ";
        _tipo = nombre[0] % 4;
        switch (nombre[0] % 4) {
            case 0: cerr << "<class=" << endl;
                break;
            case 1: cerr << "<href=" << endl;
                break;
            case 2: cerr << "<sup>" << endl;
                break;
            case 3: cerr << "<h3>" << endl;
                break;
        }
        cerr << endl << endl << endl;
        //        cout << nombre << " " << _i << " " << _tipo << endl;
    } else {
        cout << "Por favor introduce tu nombre tal y como aparece en el array nombres[] " << endl;
        exit(1);
    }
}

void liberaMemoria(string *&v){
    
    if(v != nullptr){
        delete[] v;
        v = nullptr;
    }
}

/**
 * @brief Implementa la función del enunciado 
 * @param v1 Primer vector
 * @param nv1 Número de elementos de @a v1
 * @param v3 Vector resultado. Debe reservarse memoria dentro de la función
 * @param nv3 Número de elementos de @a v3
 */

 // Apunte: No me he dado cuenta y he creado la función con otros nombres en
 // los parámetros distintos a v1 y v3. Siento esto si le supone una molestia

void funcion(string *capitulo, int ncapitulo, string *&seleccion, int &nseleccion){
    
    nseleccion = 0;
    string ocurrencia = "<sup>";
    int pos_inicial;
    
    for(int i=0; i < ncapitulo; i++){
        
        if(capitulo[i].find("<sup>") != string::npos)
            nseleccion++;
    }
    
    seleccion = new string[nseleccion];
    bool parada = false;
    int pos_a_insertar = 0;
    
    for(int i=0; i < ncapitulo; i++){
        
        if(capitulo[i].find("<sup>") != string::npos){
            int pos_inicial = capitulo[i].find("<sup>")+ocurrencia.length();
            
            int longitud = 0;
            for(int j=pos_inicial+1; j < capitulo[i].length() && !parada; j++){
                
                if(capitulo[i].at(j) != '<'){
                    longitud++;
                }
                else
                    parada = true;
            }
            
            // Como el último carácter no se ha llegado a tener en cuenta,
            // incrementamos en 1 la variable longitud
            
            longitud++;
            seleccion[pos_a_insertar] = capitulo[i].substr(pos_inicial,longitud);
            pos_a_insertar++;
                    
            // Para la siguiente iteración
                    
            parada = false;
        }
    }
}

int main() {
    ifstream findice, ficapitulo;
    ofstream fosalida;
    string nameindice = "./data/index.dat",
            namesalida = "./data/salida.dat",
            namecapitulo = "1.20.xhtml"; // Copia aquí el nombre de tu fichero de trabajo
    string *capitulo = nullptr, *seleccion = nullptr;
    int ncapitulo, nseleccion;

    string linea, cadena;
    bool salir = false;

    // Consulta tu nombre, fichero de trabajo y variante
    Introduccion("JOSE ALBERTO HOCES CASTRO"); // Copia aquí tu nombre
    
    // Abrir fichero de indice. Comprobar sólo error de apertura
    
    findice.open(nameindice);
    
    if(!findice){
        cout << "Error en la apertura del fichero " << nameindice << endl;
        exit(1);
    }

    // Buscar namecapitulo en el fichero de índce y leer el número de líneas
    
    string auxiliar;
    
    while(!salir){
        
        findice >> ncapitulo;
        findice >> auxiliar;
        
        if(auxiliar == namecapitulo)
            salir = true;
    }

    // Reservar memoria para *capitulo
    
    capitulo = new string[ncapitulo];
    
    // Abrir fichero namecapitulo dentro de "./data/"
    
    ficapitulo.open("./data/"+namecapitulo);

    // Leer las líneas en memoria dinámica
    
    for(int i=0; i < ncapitulo; i++)
        getline(ficapitulo,capitulo[i]);
    
    // Cerramos el fichero de lectura de datos
    
    ficapitulo.close();
    
    // Calcular la lista de cadenas de la variante
    
    funcion(capitulo, ncapitulo, seleccion, nseleccion);
    
    // Guardar el resultado en "./data/salida.dat"
    
    fosalida.open(namesalida);
    
    if(!fosalida){
        cout << "Error en la apertura del fichero " << namesalida << endl;
        liberaMemoria(capitulo);
        liberaMemoria(seleccion);
        exit(2);
    }
    
    for(int i=0; i < nseleccion; i++)
        fosalida << seleccion[i] << endl;
    
    // Y cerramos el fichero de salida
    
    fosalida.close();

    // Liberar la memoria
    
    liberaMemoria(capitulo);
    liberaMemoria(seleccion);
    
    return 0;
}