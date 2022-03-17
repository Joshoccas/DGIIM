/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <string>
#include<fstream>
using namespace std;
int main() {
    int i = 10;
    double d = 3.14;
    string c = "DGIIM";
    ofstream fo;
    
    fo.open("data/datos.dat");
    fo << i << endl;
    fo << d << endl;
    fo << c << endl;
    fo.close();
    
    return 0;
}
