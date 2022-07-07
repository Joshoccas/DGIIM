#include <iostream>

using namespace std;

int factorial(int n);

int main(){
  int n;

  do{
    cout << "Introduzca n: ";
    cin >>n;
  } while (n<0);

  cout << n << "! = " << factorial(n) << endl;

  return 0;
}

int factorial(int n){
  int resultado;

  if (n==0)
    resultado = 1;
  else
    resultado = n * factorial(n-1);
  return resultado;
}
