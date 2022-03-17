/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <string>
using namespace std;

#define TOPE -1000000
// Lee X (int), Lee OP("+", "x", "/") lee Y (int)
// Muestra el resultado de X OP Y
// X = 3 OP="+" Y=6
// Resultado es 9
int main(int nargs, char * args[]) {
    int X, Y, RES;
    string OP, aux;
//    
//    for (int i=0; i<nargs; i++){
//        cout << "El argumento nº"<<i<< " es " << args[i]<< endl;
//    }
    
    // Preambulo --> procesa los args y chequea errores
    
    for (int i=1; i<nargs; i+=2){
        aux = args[i];
        
        if (aux == "-X"){
            
            X=atoi(args[i+1]);
        } else if (aux == "-Y"){
            Y=stoi(args[i+1]);
        } else if (aux == "-OP"){
            OP = args[i+1];
        } else {
            cout << "Error, argumento " <<args[i] << " desconocido" << endl;
            exit(1);
        }
    }
    if(nargs != 4){
        cout << "Error número de parámetros incorrecto"<<endl;
    }
    X=atoi(args[1]); // para char *
    OP=args[2];
    Y=stod(args[3]);
    cin >> X >> OP >> Y; // Para string
    // Calculamos RES
    if (OP == "+")
        RES=X+Y;
    else if (OP == "x")
        RES = X*Y;
    else if (OP == "/")
        RES = X/Y;
    else
        RES = TOPE;
    
    // Mostrar resultado
    if(RES == TOPE){
        cout << "La operación"<<OP<< "es desconocida "<<endl;
    }else{
        cout << X << OP << Y << " es igual a " << RES;
    }
    return 0;
}