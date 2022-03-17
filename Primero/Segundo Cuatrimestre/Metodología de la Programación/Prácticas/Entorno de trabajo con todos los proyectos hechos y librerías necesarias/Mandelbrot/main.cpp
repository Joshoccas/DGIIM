/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: adrian
 *
 * Created on 22 de marzo de 2021, 12:53
 */


#include <iostream>
#include <fstream> // for files manipulation
#include <complex> // for complex numbersusing namespace std;

using namespace std;

float width =  1000;
float height = 1000;

int value ( int x, int y)  
{
    complex<float> point((float)2*x/width-1.5, (float)2*y/height-1);
// we divide by the image dimensions to get values smaller than 1
// then apply a translation
    complex<float> z(0, 0);
    unsigned int nb_iter = 0;
    while (abs (z) < 100 && nb_iter <= 34) {
           z = z * z + point;
           nb_iter++;
    }
    if (nb_iter < 34) return (255*nb_iter)/33;
    else return 0;
}

/*
 * 
 */
int main() {
   
    
    
    ofstream my_Image ("mandelbrot.ppm"); 
    if (my_Image.is_open ()) {
        my_Image << "P3\n" << width << " " << height << " 255\n";
        for (int i = 0; i < width; i++) {
             for (int j = 0; j < height; j++)  {   
                 
                 int val = value(j, i); 
                  my_Image << val << ' ' << 0 << ' ' << 0 << "\n";
             }
        }
        my_Image.close();
    }
    else cout << "Could not open the file";
    
    return 0;
}