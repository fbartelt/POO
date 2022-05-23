#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "matrix.h"
using namespace std;

int main(){
  ifstream in("myMatrix.txt");
  Matrix Y;
  Matrix X(3, 1), A(3,3), C(3,3);
  Matrix Z(3,2,7.0);
  Matrix W(in);
  cout << "Matrizes definidas:" << endl;
  cout << "Y:" << endl << Y << endl;
  cout << "X:" << endl << X << endl;
  cout << "A:" << endl << A << endl;
  cout << "C:" << endl << C << endl;
  cout << "Z:" << endl << Z << endl;
  cout << "W:" << endl << W << endl;

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% // 
  cout << "Testes de Operacoes" << endl << "-----------------------------------" << endl;
  
  A(2,1) = 10;
  cout << "A(2,1)=10:" << endl << A << endl;

  C = A + A;
  cout << "C = A + A:" << endl << C << endl;

  C -= A;
  cout << "C -= A:" << endl << C << endl;

  A = C - A;
  cout << "A = C - A:" << endl << A << endl;

  A += A;
  cout << "A += A:" << endl << A << endl;

  A = ~C;
  cout << "A = ~C:" << endl << A << endl;

  X *= 2;
  cout << "X *= 2:" << endl << X << endl;
  
  C = A * X;
  cout << "C = A * X:" << endl << C << endl;

  if(A == C)
    cout << "A igual a  C" << endl;
  else
    cout << "A nao eh igual a C" << endl;

  if(X != Y)
    cout << "X eh diferente de Y" << endl;
  else
    cout << "X nao eh diferente de Y" << endl;
  
  cout << "cout << Z << endl; :" << endl;
  cout << Z << endl;

  cin >> Y; // Insira os elementos espacados por white spaces. Enter ou qualquer caracter nao numerico para parar o cin.
  cout << "cin >> Y:" << endl << Y << endl;
  
  vector<double> vec{1, 2, 3, 4, 5, 6};
  Matrix M(2, 3, vec);
  cout << "Construtor de Matriz via ponteiro--> Matrix M(2, 3, vec); :" << endl << M << endl;

  vector<double> vec2{1, 2, 3, 4};
  Matrix MM(3, 2, vec2);
  cout << "Construtor via vector, onde o vetor tem menos elementos que o tamanho da matriz (Preenchimento por 0s)." << endl;
  cout << "vector<double> vec2{1, 2, 3, 4}; Matrix MM(3, 2, vec); :" << endl << MM << endl;

  Matrix N(M * MM);
  cout << "Construtor por Referencia--> Matrix N(M * MM)" << endl << N << endl;

  auto test = (N * 2).get(1, 1);
  cout << "Getter de elemento--> auto test = (N * 2).get(1, 1);" << endl << test << endl;

  N.reshape(4, 1);
  cout << "Trocar as dimensoes da matriz--> N.reshape(4, 1); :" << endl << N << endl;

 // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% // 
  cout << "Testes de Excecoes" << endl << "-----------------------------------" << endl;

  ifstream in2("myThrowMatrix1.txt");
  try{
    cout << "Arquivo tem 1 elemento a menos--> Matrix e1(in2); :" << endl;
    Matrix e1(in2);
  }
  catch(const exception& e){
    cout << e.what() << '\n' << endl;
  }

  try{
    cout << "Tentando acessar elemento inexistente--> auto a = N(0, 0); :" << endl;
    auto a = N(0, 0);
  }
  catch(const exception& e){
    cout << e.what() << '\n' << endl;
  }

  try{
    cout << "Tentando alterar dimensoes da matriz para valores nao positivos--> N.reshape(-1, -1); :" << endl;
    N.reshape(-1, -1);
  }
  catch(const exception& e){
    cout << e.what() << '\n' << endl;
  }

  try{
    cout << "Tentando alterar dimensoes da matriz para um formato com mais elementos--> N.reshape(100, 100); :" << endl;
    N.reshape(100, 100);
  }
  catch(const exception& e){
    cout << e.what() << '\n' << endl;
  }

  try{
    cout << "Tentando alterar elemento inexistente--> N(10, 10) = 100; :" << endl;
    N(10, 10) = 100;
  }
  catch(const exception& e){
    cout << e.what() << '\n' << endl;
  }

  try{
    cout << "Tentando realizar soma matricial (4 x 1) + (1 x 4) --> Matrix e2 = N + ~N;" << endl;
    Matrix e2 = N + ~N;
  }
  catch(const exception& e){
    cout << e.what() << '\n' << endl;
  }

  try{
    cout << "Tentando realizar subtracao matricial (1 x 4) - (4 x 1) --> Matrix e2 = ~N - N;" << endl;
    Matrix e2 = ~N - N;
  }
  catch(const exception& e){
    cout << e.what() << '\n' << endl;
  }

  try{
    cout << "Tentando realizar multiplicacao matricial (4 x 1) * (4 x 1) --> Matrix e2 = N * N;" << endl;
    Matrix e2 = N * N;
  }
  catch(const exception& e){
    cout << e.what() << '\n' << endl;
  }

  try{
    cout << "Tentando realizar multiplicacao matricial (4 x 1) * (4 x 1) --> N *= N;" << endl;
    N *= N;
  }
  catch(const exception& e){
    cout << e.what() << '\n' << endl;
  }

  try{
    cout << "Tentando alterar os elementos de uma matriz por entrada padrao, com numero diferente de elementos:" << endl;
    stringstream s;
    s << "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15";
    s >> N;
  }
  catch(const exception& e){
    cout << e.what() << '\n' << endl;
  }
  
  return 0;
}