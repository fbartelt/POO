#include <iostream>
#include <sstream>
#include <string>

#include "Agenda.h"
using namespace std;

int main() {
  string qty_s;
  int qty;
  cout << "Digite quantas pessoas quer adicionar a agenda: ";
  getline(cin, qty_s);
  istringstream s(qty_s);
  s >> qty;
  Agenda A(qty);
  cout << endl
       << "Total de Amigos na agenda: " << A.getAmigos()
       << "\nTotal de Conhecidos na agenda: " << A.getConecidos() << endl
       << endl;
  A.addInformacoes();
  A.imprimeAniversarios();
  A.imprimeEmail();

  return 0;
}