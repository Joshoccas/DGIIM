#include <cstdlib>
#include <iostream>

using namespace std;

double potencia(double base, int exponente);

int main(){
  double base, exponente;

  cout << "Base: ";
  cin >> base;
  do{
    cout << "Exponente: ";
    cin >> exponente;
  } while (exponente<0);

  cout << base << '^' << exponente << " = " << potencia(base, exponente) << endl;
  system("PAUSE");
  return 0;
}

double potencia(double base, int exponente){
  if (exponente==0)
    return 1;
  else
    return base * potencia(base, exponente-1);
}
