#include <cstdlib>
#include <iostream>

using namespace std;

int sumatoria(int n);

int main(){
  int n;

  do{
    cout << "Introduzca n: ";
    cin >> n;
  } while (n<1);

  cout << "Sumatoria de 1 a " << n << ": " << sumatoria(n) << endl;
  system("PAUSE");
  return 0;
}

int sumatoria(int n){
  if (n==1)
    return 1;
  else
    return n + sumatoria(n-1);
}
