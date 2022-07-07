#include <cstdlib>
#include <iostream>

using namespace std;

int SumaVectorHasta(int v[], int n);

int main(){
  const int TAM=100;
  int v[TAM], util_v, i;

  do{
    cout << "Introduzca el número de datos: ";
    cin >> util_v;
  } while (util_v<=0);

  cout << "Introduzca los " << util_v << " datos: ";
  for(i=0; i<util_v; i++)
    cin >> v[i];

  cout << "La suma del vector es " << SumaVectorHasta(v,util_v-1) << endl;

  system("PAUSE");
  return 0;
}

int SumaVectorHasta(int v[], int pos){
  if (pos==0)
    return v[0];
  else
    return v[pos] + SumaVectorHasta(v, pos-1);
}
