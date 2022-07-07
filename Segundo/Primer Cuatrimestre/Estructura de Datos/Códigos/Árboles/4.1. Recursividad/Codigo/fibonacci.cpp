#include <cstdlib>
#include <iostream>

int fibonacci(int n);

using namespace std;

int main(){
  int n;

  cout << "Introduzca n: ";
  cin >> n;
  while(n>=0){
    cout << "Fib(" << n << ") = " << fibonacci(n) << endl;
    cout << "Introduzca n: ";
    cin >> n;
  };

  system("PAUSE");
  return 0;

}

int fibonacci(int n){
  if (n==0)
    return 0;
  else if (n==1)
    return 1;
  else
    return fibonacci(n-1) + fibonacci(n-2);
}

//int fibonacci(int n){
//  int actual=0, n_1=1, n_2=0, i;
//
//  if (n == 0)
//    actual = 0;
//  else if (n == 1)
//    actual = 1;
//  else
//    for (i=2; i<=n; i++){
//      actual = n_1 + n_2;
//      n_2 = n_1;
//      n_1 = actual;
//    }
//  return actual;
//}
