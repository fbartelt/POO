#include "Ponto2D.h"
#include <iostream>
using namespace std;

int main(){
  Ponto2D p1;
  Ponto2D p2(3, 4);
  cout << "p1.print()" << endl;
  p1.print();
  cout << "p2.print()" << endl;
  p2.print();
  cout << "p1.distToOrig  " << p1.distToOrig() << endl;
  cout << "p2.distToOrig  " << p2.distToOrig() << endl;
  Ponto2D p3(p2);
  cout << "Ponto2D p3(p2):" << endl;
  p3.print();
  p3.sumOf(p2);
  cout << "p3.sumOf(p2):" << endl;
  p3.print();
  cout << "p1.distTo(p3) " << p1.distTo(p3) << endl;
  cout << "p2.distTo(p3) " << p2.distTo(p3) << endl;
  --p2;
  cout << "p2--; p2.print(): " << endl;
  p2.print();
  Ponto2D p4 = p3.sumOfWithReturn(p2);
  cout << "p4 = p3.sumOfWithReturn(p2); p4.print(): " << endl;
  p4.print();
  cout << "p5 = p4 + p3:" << endl;
  Ponto2D p5 = p4 + p3;
  return 0;
}