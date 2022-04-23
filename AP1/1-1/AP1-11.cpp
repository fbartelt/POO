#include <string>
#include <fstream>
#include <iostream>
using namespace std;

/**
1.1. Escreva um programa que abra um arquivo e conte o número de espaços em branco do arquivo.
**/

int main(){
  char buffer;
  int blank_count = 0;
  const char WHITE_SPACE(32);
  fstream file("AP1-11.cpp");
  while((file.get(buffer), file.eof()) == false){
    if(file.peek() == WHITE_SPACE){
      blank_count += 1;
    };
  }
  cout << "Número de espaços em branco: " << blank_count << endl;
  return(0);
}