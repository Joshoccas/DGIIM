 /**
  * @file imageIO.cpp
  * @brief Fichero con definiciones para la E/S de imágenes
  *
  * Permite la E/S de archivos de tipo PGM,PPM
  *
  */

#include <string>

#include <imageIO.h>

#include <fstream>
using namespace std;


ImageKind ReadKind(ifstream& f){
  char c1,c2;
  ImageKind res= IMG_UNKNOWN;

  if (f){
    c1=f.get();
    c2=f.get();
    if (f && c1=='P')
      switch (c2) {
        case '5': res= IMG_PGM; break;
        case '6': res= IMG_PPM; break;
        default: res= IMG_UNKNOWN;
      }
  }
  return res;
}

// _____________________________________________________________________________

ImageKind ReadImageKind(const char *nombre){
  ifstream f(nombre);
  return ReadKind(f);
}


// _____________________________________________________________________________

char SkipWhitespaces (ifstream& f){
  char c;
  do{
    c= f.get();
  } while (isspace(c));
  f.putback(c);
  return c;
}

// _____________________________________________________________________________

bool ReadHeader (ifstream& f, int& rows, int& cols){
    int maxvalor;
    string linea;
    while (SkipWhitespaces(f) == '#')
      getline(f,linea);
    f >> cols >> rows >> maxvalor;
    
    if (/*str &&*/ f && rows>0 && rows<5000 && cols>0 && cols<5000){
        f.get(); // Saltamos separador
        return true;
    }
    else 
      return false;
}



// _____________________________________________________________________________

unsigned char *ReadPGMImage (const char *path, int& rows, int& cols){
  unsigned char *res=0;
  rows=0;
  cols=0;
  ifstream f(path);
  
  if (ReadKind(f) == IMG_PGM){
    if (ReadHeader(f, rows, cols)){
      res= new unsigned char[rows*cols];
      f.read(reinterpret_cast<char *>(res),rows*cols);
      if (!f){
        delete[] res;
        res= 0;
      }
    }
  }
  return res;
}

// _____________________________________________________________________________

bool WritePGMImage (const char *nombre, const unsigned char *datos,
                    const int rows, const int cols){
  ofstream f(nombre);
  bool res= true;
  
  if (f){
    f << "P5" << endl;
    f << cols << ' ' << rows << endl;
    f << 255 << endl;
    f.write(reinterpret_cast<const char *>(datos),rows*cols);
    if (!f)
      res=false;
  }
  return res;
}


/* Fin Fichero: imagenES.cpp */

