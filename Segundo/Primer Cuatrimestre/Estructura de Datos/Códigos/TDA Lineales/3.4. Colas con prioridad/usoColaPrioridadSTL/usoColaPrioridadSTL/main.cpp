#include <iostream>
#include <queue>

using namespace std;

struct Pareja{
  int nota;
  string dni;
  bool operator<(const struct Pareja & otra) const{
    return (this->nota < otra.nota);
  }
};

int main(){
  priority_queue<Pareja> c;
  Pareja p;
  
  cout << "Escriba una nota: ";
  cin >> p.nota;
  while(p.nota >=0 && p.nota <=10){
    cout << "Escriba un dni: ";
    cin >> p.dni;
    c.push(p);
    cout << "Escriba una nota: ";
    cin >> p.nota;
  }
  cout << "DNIs ordenados por nota:" << endl;
  while(!c.empty()){
    p = c.top();
    cout << "DNI: " << c.top().dni << " Nota: "
    << c.top().nota << endl;
    c.pop();
  }
  return 0;
}
