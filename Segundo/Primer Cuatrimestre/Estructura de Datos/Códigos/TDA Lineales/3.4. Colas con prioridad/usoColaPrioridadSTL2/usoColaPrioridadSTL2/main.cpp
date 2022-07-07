#include <iostream>
#include <queue>

using namespace std;

int main(){
  priority_queue<pair<int, string>> c;
  pair<int, string> p;
  
  cout << "Escriba una nota: ";
  cin >> p.first;
  while(p.first >=0 && p.first <=10){
    cout << "Escriba un dni: ";
    cin >> p.second;
    c.push(p);
    cout << "Escriba una nota: ";
    cin >> p.first;
  }
  cout << "DNIs ordenados por nota:" << endl;
  while(!c.empty()){
    p = c.top();
    cout << "DNI: " << c.top().second << " Nota: "
    << c.top().first << endl;
    c.pop();
  }
  return 0;
}

