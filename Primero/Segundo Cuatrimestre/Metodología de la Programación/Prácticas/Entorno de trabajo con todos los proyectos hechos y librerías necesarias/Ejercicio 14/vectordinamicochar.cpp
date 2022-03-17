/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "vectordinamicochar.h"

void inicializar (char* &arraychar,int nCarac){
    arraychar = nullptr;
    nCarac = 0;
}

void liberar(char* &arraychar,int &nCarac){
    delete[] arraychar;
    arraychar = nullptr;
    nCarac = 0;
}

void mostrar(std::ostream& flujo, char*arraychar, int nCarac){
    for(int i=0; i < nCarac; i++){
        flujo << arraychar[i];
    }
}

void redimensionar (char* &arraychar, int& nCarac, int aumento){
    if(nCarac+aumento > 0){
        char *v_ampliado = new char[nCarac+aumento];
        for (int i=0; (i<nCarac) && (i<nCarac+aumento); i++)
            v_ampliado[i] = arraychar[i];
        delete[] arraychar;
        arraychar = v_ampliado;
        nCarac=nCarac+aumento;
    }
}

void aniadir(char* &arraychar, int& nCarac,char caracter){
    redimensionar(arraychar,nCarac,1);
    arraychar[nCarac-1]=caracter;
}

void leer(std::istream& flujo, char* &array, int& nchar){
    char caracter;
    
    while(flujo.get(caracter)){
        aniadir(array, nchar, caracter);
    }
}