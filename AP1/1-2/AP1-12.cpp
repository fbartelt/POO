#include <iostream>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
using namespace std;

/**
1.2. Dado um vetor de números inteiros positivos aleatórios entrados via teclado (número negativo indica fim da entrada dos dados), faça um programa utilizando a classe template vector para comprimir o vetor suprimindo as repetições de números vizinhos através da contagem do número de repetições de cada um da seguinte forma:

    Vetor de entrada: 1 1 1 4 1 1 4 4 25 67 67 67 67 2 2
    Vetor de saída: 3 1 1 4 2 1 2 4 1 25 4 67 2 2 
**/

int main(){
  vector<int> v;
  vector<int> vout;
  string in;
  int number;
  int counter = 0;
  
  cout << "Insira um vetor de números inteiros positivos" << endl;
  getline(cin, in);
  cout << in;
  istringstream stream(in);
  
  while (stream >> number)
    v.push_back(number);
  number = v[0];

  for(int i: v){
    if(i != number){
      vout.push_back(counter);
      vout.push_back(number);
      number = i;
      counter = 1;
    }

    else{
      counter++;
    }
  }
  vout.push_back(counter);
  vout.push_back(number);

  cout << endl;

  for(int i: vout){
    cout << ' ' << i;
  }
  return(0);
}