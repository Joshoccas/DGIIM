/*
 NOMBRE Y APELLIDOS: Pablo Ramírez Gonzalvo
 DNI: 78006474L
 GRUPO DE PRACTICAS: Martes
 EXAMEN: online 
  */

using namespace std;

#include <iostream>
#include <string>
#include <fstream>

void liberaMemoria(char *&s1, char *&s2){
    
    if(s1 != nullptr){
        delete[] s1;
        s1 = nullptr;
    }
    
    if(s2 != nullptr){
        delete[] s2;
        s2 = nullptr;
    }
}

void mostrar(char *s, int n){
	cout << "{";
    for(int i = 0; i < n; i++)
		cout << s[i];
		
	cout << "}" << endl;
}

void unirconjuntos(char *s1, int n1, char *s2, int n2, char *&unir, int &tamaniounir){
    
    tamaniounir = 0;
    int _elementos_comunes = 0;
    bool sigo = true;
    
    for(int i=0; i < n1; i++){
        
        for(int j=0; (j < n2)&&sigo; j++){
            
            if(s1[i] == s2[j]){
                _elementos_comunes++;
                sigo = false;
            }
        }
        
        sigo = true;
    }
    
    tamaniounir = n1 + (n2-_elementos_comunes);
    unir = new char[tamaniounir];
    
    for(int i=0; i < n1; i++)
        unir[i]=s1[i];
    
    int pos = n1;
    
    for(int j=0; j < n2; j++){
        
        for(int i=0; (i < n1) && sigo; i++){
            
            if(s2[j] == s1[i]){
                sigo = false;
            }
        }
    
        if(sigo){
            unir[pos]=s2[j];
            pos++;
        }

        sigo = true;
    }
}


void interseccion(char *s1, int n1, char *s2, int n2, char *&interseccion, int &tamaniointer){
    
    tamaniointer = 0;
    bool sigo = true;
    
    for(int i=0; i < n1; i++){
        
        for(int j=0; (j < n2)&&sigo; j++){
            
            if(s1[i] == s2[j]){
                tamaniointer++;
                sigo = false;
            }
        }
        
        sigo = true;
    }
    
    interseccion = new char[tamaniointer];
    int pos = 0;
    
    for(int i=0; i < n1; i++){
        
        for(int j=0; (j < n2)&&sigo; j++){
            
            if(s1[i] == s2[j]){
                interseccion[pos]=s1[i];
                pos++;
                sigo = false;
            }
        }
        
        sigo = true;
    }
}


void diferencia(char *s1, int n1, char *s2, int n2, char *&diferencia, int &tamaniodif){
    
    tamaniodif = 0;
    bool no_repetido = true;
    
    for(int i=0; i < n1; i++){
        
        for(int j=0; (j < n2)&&no_repetido; j++){
            
            if(s1[i] == s2[j])
                no_repetido = false;
        }
        
        if(no_repetido)
            tamaniodif++;
        
        no_repetido = true;
    }
    
    for(int j=0; j < n2; j++){
        
        for(int i=0; (i < n1)&&no_repetido; i++){
            
            if(s2[j] == s1[i])
                no_repetido = false;
        }
        
        if(no_repetido)
            tamaniodif++;
        
        no_repetido = true;
    }
    
    diferencia = new char[tamaniodif];
    int pos = 0;
    
    for(int i=0; i < n1; i++){
        
        for(int j=0; (j < n2)&&no_repetido; j++){
            
            if(s1[i] == s2[j])
                no_repetido = false;
        }
        
        if(no_repetido){
            diferencia[pos] = s1[i];
            pos++;
        }
        
        no_repetido = true;
    }
    
    for(int j=0; j < n2; j++){
        
        for(int i=0; (i < n1)&&no_repetido; i++){
            
            if(s2[j] == s1[i])
                no_repetido = false;
        }
        
        if(no_repetido){
            diferencia[pos] = s2[j];
            pos++;
        }
        
        no_repetido = true;
    }
}
void calcularCoeficiente(char *s1, int n1, char *s2, int n2, double &coef){
    
    coef = 0;
    int tamaniounir;
    char *unir = nullptr;
    unirconjuntos(s1, n1, s2 ,n2, unir, tamaniounir);
    
    int tamaniointer;
    char *inter = nullptr;
    interseccion(s1, n1, s2, n2, inter, tamaniointer);
    
    liberaMemoria(unir,inter);
    
    coef = double(tamaniointer)/tamaniounir;
}


void test(char *s1, int n1, char *s2, int n2){
       // definir variables necesarias
    // mostrar s1 y s2
    // calcular union entre s1 y s2
    // mostrar conjunto union
    //calcular interseccion entre s1 y s2
    // mostrar conjunto interseccion
    
    // mostrar tama�os de los conjunto union e interseccion
    // y el valor del coeficiente
    
    char *unir = nullptr;
    int tamaniounir;
    char *inter = nullptr;
    int tamaniointer;
    char *difer = nullptr;
    int tamaniodif;
    double coef;
    
    unirconjuntos(s1, n1, s2 ,n2, unir, tamaniounir);
    interseccion(s1, n1, s2, n2, inter, tamaniointer);
    diferencia(s1, n1, s2, n2, difer, tamaniodif);
    calcularCoeficiente(s1, n1, s2, n2, coef);

    cout << "set 1 -> ";
    mostrar(s1, n1);
    cout << "set 2 -> ";
    mostrar(s2, n2);
    cout << "union -> ";
    mostrar(unir, tamaniounir);
    cout << "interseccion -> " << endl;
    mostrar(inter, tamaniointer);
    cout << "diferencia -> " << endl;
    mostrar(difer, tamaniodif);
    cout << "coeficiente -> " << tamaniointer << " / " << tamaniounir << " = " << coef << endl;
    
    liberaMemoria(s1,s2);
    liberaMemoria(unir,inter);
    liberaMemoria(difer,unir);
}

int main(){
    char *s1 = nullptr;
    char *s2 = nullptr;
    int n1, n2;
    string ifilename;
    ifstream fi;
    
    cout << "Introduzca el nombre del fichero: ";
    cin >> ifilename;
    
    // Abrimos el fichero
    
    fi.open(ifilename);
    
    if(!fi){
        cout << "Error al abrir el fichero " << ifilename;
        exit(1);
    }
    
    // Leemos el tamaño del primer vector
    
    fi >> n1;
    
    // Reservamos la memoria necesaria para s1 y comenzamos a almacenar datos
    
    s1 = new char[n1];
    
    for(int i=0; i < n1; i++)
        fi >> s1[i];
    
    // Se comprueba si han habido errores de lectura
    
    if(!fi){
        cout << "Error en la lectura de datos";
        liberaMemoria(s1,s2);
        fi.close();
        exit(2);
    }
    
    // Y mostramos el vector s1
    
    mostrar(s1,n1);
    
    // Repetimos el mismo proceso con s2
    
    // Leemos el tamaño del primer vector
    
    fi >> n2;
    
    // Reservamos la memoria necesaria para s1 y comenzamos a almacenar datos
    
    s2 = new char[n2];
    
    for(int i=0; i < n2; i++)
        fi >> s2[i];
    
    // Se comprueba si han habido errores de lectura
    
    if(!fi){
        cout << "Error en la lectura de datos";
        liberaMemoria(s1,s2);
        fi.close();
        exit(3);
    }
    
    fi.close();
    
    // Y mostramos el vector s1
    
    mostrar(s2,n2);
    
    // Y finalmente empleamos el método test para hallar el coeficiente
    
    test(s1, n1, s2, n2);
}