/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: joshoc7
 *
 * Created on 13 de abril de 2021, 16:02
 */

#include <iostream>
#include <string>
#include<fstream>
using namespace std;
int main() {
    int i = -1;
    double d = -1;
    string c = "";
    ofstream fo;
    ifstream fi;
    
    fi.open("data/datos.dat");
    if (fi) {
        fi >> i;
        fi >> d;
        fi >> c;
        if(fi){
            fi.close();
            cout << i << endl;
            cout << d << endl;
            cout << c << endl;
        }else{
            cout << "Error en la LECTURA del fichero" << endl;
        }
    }else{
        cout << "Error en la APERTURA del fichero" << endl;
    }
    
    return 0;
}

