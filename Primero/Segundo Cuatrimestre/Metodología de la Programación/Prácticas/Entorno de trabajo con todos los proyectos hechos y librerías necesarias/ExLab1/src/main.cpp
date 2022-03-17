/**
 * @file main.cpp
 * @brief Examen de laboratorio 
 * Universidad de Granada
 * Metodología de la Programación 
 * @nombre_del_alumno:  
 * 
 * @warning Por favor, rellene las funciones que se indican
 * @warning Es obligatorio el uso de estas funciones
 */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**
@brief Imprime el contenido de un vector de string
@param v 	Vector de string
@param n	Número de elementos que contiene @a v
 */
void imprimirVector(const string *v, const int n) {
    if (v != nullptr && n >= 0) {
        cout << n << " elementos" << endl;
        for (int i = 0; i < n; i++)
            cout << "[" << i << "] = " << v[i] << endl;
    }
}

/**
 * @brief Implementa la función del enunciado 
 * @param v1 Primer vector
 * @param nv1 Número de elementos de @a v1
 * @param v2 Segundo vector
 * @param nv2 Número de elementos de @a v2
 * @param v3 Vector resultado. Debe reservarse memoria dentro de la función
 * @param nv3 Número de elementos de @a v3
 */
void funcion(string const *v1, int nv1, string *v2, int nv2, string * &v3, int &nv3){
    
    nv3 = 0;
    bool stop = false;
    
    for(int i=0; i < nv1; i++){
        
        for(int j=0; (j < nv2)&&!stop; j++){
            
            if(v1[i] == v2[j]){
                nv3++;
                stop = true;
            }
        }
        
        stop = false;
    }
    
    v3 = new string[nv3];
    int pos = 0;
    
    for(int i=0; i < nv1; i++){
        
        for(int j=0; (j < nv2)&&!stop; j++){
            
            if(v1[i] == v2[j]){
                v3[pos]=v1[i];
                pos++;
                stop = true;
            }
        }
        
        stop = false;
    }
}

void liberaMemoria(string *&v1, string *&v2, string *&v3){
    
    if(v1 != nullptr){
        delete [] v1;
        v1 =  nullptr;
    }
    
    if(v2 != nullptr){
        delete [] v2;
        v2 =  nullptr;
    }
    
    if(v3 != nullptr){
        delete [] v3;
        v3 =  nullptr;
    }
}

int main() {
    int nv1 = 0, nv2 = 0, nv3 = 0;
    string *v1 = nullptr, *v2 = nullptr, *v3 = nullptr;
    string namefi1, namefi2, namefo;
    ifstream fi1, fi2;
    ofstream fo;
    int i;
    // Examen: Leer vector v1
    cout << "Por favor introduzca el nombre del primer fichero (carpeta ./data/): ";
    cin >> namefi1;
    // Abrir el fichero
    
    fi1.open(namefi1);
    
    if(!fi1){
        cout << "El fichero " << namefi1 << " no se ha podido abrir " << endl;
        exit(1);
    }
        
            
    // Leer número de elementos
    
    fi1 >> nv1;
    
    // Dimensionar la memoria
    
    v1 = new string[nv1];
    
    // Leer los datos en memoria
    
    for(int i=0; i < nv1; i++)
        fi1 >> v1[i];
    if(!fi1){
        cout << "El fichero " << namefi1 << " contiene un error en los datos " << endl;
        liberaMemoria(v1,v2,v3);
        fi1.close();
        exit(1);
    }
    
    fi1.close();
    
    // Imprimir los datos leídos
    imprimirVector(v1, nv1);

    // Examen: Leer vector B
    cout << "Por favor introduzca el nombre del segundo fichero (carpeta ./data/): ";
    cin >> namefi2;
    
    // Abrir el fichero
    
    fi2.open(namefi2);
    
    if(!fi2){
        cout << "El fichero " << namefi2 << " no se ha podido abrir " << endl;
        liberaMemoria(v1,v2,v3);
        exit(2);
    }
            
    // Leer número de elementos
    
    fi2 >> nv2;
    
    // Dimensionar la memoria
    
    v2 = new string[nv2];
    
    // Leer los datos en memoria
    
    for(int i=0; i < nv2; i++)
        fi2 >> v2[i];
    
    if(!fi2){
        cout << "El fichero " << namefi2 << " contiene un error en los datos " << endl;
        liberaMemoria(v1,v2,v3);
        fi2.close();
        exit(3);
    }
    
    fi2.close();
    // Imprimir los datos leídos
    imprimirVector(v2, nv2);

    // Examen: Calcular resultado. La memoria para el resultado se reserva dentro de la función
    funcion(v1, nv1, v2, nv2, v3, nv3);

    // Examen: Mostrar resultado
    imprimirVector(v3, nv3);
    
//    // Guardar resultado
//    cout << "Por favor, introduzca el nombre del fichero de resultados (carpeta ./data/): ";
//    cin >> namefo;
    // Abrir fichero de salida
    
    fo.open(namefo);
    
    if(!fo){
        cout << "El fichero " << namefo << " no se ha podido abrir " << endl;
        liberaMemoria(v1,v2,v3);
        exit(4);
    }

    // Guardar número de datos resultado
    
    fo << nv3 << endl;
            
    // Guardar los datos
    
    for(int i=0; i<nv3; i++)
        fo << v3[i] << endl;
    
    if(!fo){
        cout << "El fichero " << namefo << " ha dado un error de datos " << endl;
        liberaMemoria(v1,v2,v3);
        fo.close();
        exit(5);
    }
            
    // Examen: Terminación del programa

    // asegurarse que, pase lo que pase, se libera la memoria, TODA la memoria: es decir
    // que valgrind se ejecuta sin errores.
    
    liberaMemoria(v1,v2,v3);
            
    return 0;
}
