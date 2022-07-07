#include <cstdlib>
#include <iostream>

using namespace std;

int producto(int a, int b);

int main(){
  int a, b;

  do{
    cout << "Introduzca a y b: ";
    cin >> a >> b;
  } while (a<0 || b<0);

  cout << a << " * " << b <<  " = " << producto(a,b) << endl;
  system("PAUSE");
  return 0;
}

int producto(int a, int b){
  if (a==0 || b==0)
    return 0;
  else
    return a + producto(a, b-1);
}
