/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   vectordinamicochar.h
 * Author: joshoc7
 *
 * Created on 12 de abril de 2021, 17:23
 */

#ifndef VECTORDINAMICOCHAR_H
#define VECTORDINAMICOCHAR_H
#include<iostream>

void inicializar(char* &arraychar,int &nCarac);
void liberar(char* &arraychar,int &nCarac);
void mostrar(std::ostream& flujo, char*arraychar, int nCarac);
void redimensionar (char* &arraychar, int& nCarac, int aumento);
void aniadir(char* &arraychar, int& nCarac,char caracter);
void leer(std::istream& flujo, char* &array, int& nchar);

#endif /* VECTORDINAMICOCHAR_H */

