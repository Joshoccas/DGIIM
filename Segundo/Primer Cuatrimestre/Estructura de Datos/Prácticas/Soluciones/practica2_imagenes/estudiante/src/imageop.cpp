/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <iostream>
#include <cmath>
#include <image.h>

#include <cassert>

// Invierte
void Image::Invert(){

    for (int i=0; i<size(); i++)
        set_pixel(i,255-get_pixel(i));
}

Image Image::Crop(int nrow, int ncol, int height, int width) const {

    Image resultado(height, width);

    for(int i=0; i < height; i++){
        for(int j=0; j < width; j++)
            resultado.set_pixel(i,j, get_pixel(nrow+i,ncol+j));
    }

    return resultado;
}

Image Image::Zoom2X() const{

    Image resultado(2*get_rows()-1,2*get_cols()-1);

    for(int i=0; i < get_rows(); i++){
        for(int j=0; j < get_cols(); j++)
            resultado.set_pixel(2 * i, 2 * j, get_pixel(i, j));
    }

    for(int i=0; i < resultado.get_rows(); i+=2){
        for(int j=1; j < resultado.get_cols(); j+=2)
            resultado.set_pixel(i,j,round((resultado.get_pixel(i,j-1)+resultado.get_pixel(i,j+1))/2.0));
    }

    for(int i=1; i < resultado.get_rows(); i+=2){
        for(int j=0; j < resultado.get_cols(); j++) {

            if(j%2 == 0)
                resultado.set_pixel(i, j, round((resultado.get_pixel(i-1, j) + resultado.get_pixel(i+1, j)) / 2.0));
            else
                resultado.set_pixel(i, j, round((resultado.get_pixel(i-1, j-1 ) + resultado.get_pixel(i-1,j+1)+resultado.get_pixel(i+1,j-1)+resultado.get_pixel(i+1,j+1)) / 4.0));
        }
    }

    return resultado;
}

double Image::Mean (int i, int j, int height, int width) const {
    int suma=0;
    for (int raw=0; raw<height; raw++)
        for (int col=0; col<width; col++)
            suma+=get_pixel(raw+i, col+j);
    double resultado=1.0*suma/(height*width);
    return resultado;
}

    Image Image::Subsample(int factor) const {
        int ncols=get_cols()/factor, nrows=get_rows()/factor;
        Image resultado(nrows, ncols);
        for (int i = 0; i < nrows; i++)
            for (int j = 0; j < ncols; j++) {
                byte value = round(Mean(i * factor, j * factor, factor, factor));
                resultado.set_pixel(i, j, value);
            }

        return resultado;
    }

void Image::AdjustContrast (byte in1, byte in2, byte out1, byte out2) {

    double primer_tramo = 1.0*out1/in1;
    double segundo_tramo = 1.0*(out2-out1)/(in2-in1);
    double tercer_tramo = 1.0*(255-out2)/(255-in2);

    for(int k = 0; k < size(); k++) {
        if (get_pixel(k) < in1)     // duda
            set_pixel(k, round(primer_tramo * get_pixel(k)));
        else if (get_pixel(k) <= in2)
            set_pixel(k, round(out1 + segundo_tramo * (get_pixel(k) - in1)));
        else if (get_pixel(k) <= 255)
            set_pixel(k, round(out2 + tercer_tramo * (get_pixel(k) - in2)));
    }
}

void Image::ShuffleRows() {
    const int p = 9973;
    byte **aux = new byte * [rows];
    // Primero realizamos la copia

    for (int r=0; r<rows; r++) aux[r] = img[r];

    for(int r=0; r<rows; r++){
        int newr = r*p%rows;
        img[r] = aux[newr];
    }

    delete [] aux;
    aux = nullptr;
}
