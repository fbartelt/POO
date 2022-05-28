#ifndef AGENDA_H
#define AGENDA_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Pessoa.h"
using namespace std;

class Agenda {
 private:
  vector<Pessoa *> pessoas;
  int amigos = 0;
  int conhecidos = 0;

 public:
  Agenda(int qty_pessoas);
  int getAmigos() const { return amigos; }
  int getConecidos() const { return conhecidos; }
  void addInformacoes();
  void imprimeAniversarios() const;
  void imprimeEmail() const;
  ~Agenda();
};

Agenda::Agenda(int qty_pessoas) {
  srand((unsigned int)time(NULL));
  for (int i = 0; i < qty_pessoas; i++) {
    int r = (rand() % 2) + 1;
    if (r == 1) {
      Amigo *a = new Amigo;
      pessoas.push_back(a);
      amigos += 1;
    } else {
      Conhecido *c = new Conhecido;
      pessoas.push_back(c);
      conhecidos += 1;
    }
  }
}

Agenda::~Agenda() {
  for (auto i : pessoas) {
    delete i;
  }
  pessoas.clear();
}

void Agenda::addInformacoes() {
  for (auto person : pessoas) {
    person->addInformacoes_();
  }
}

void Agenda::imprimeAniversarios() const {
  cout << endl << "Aniversarios:" << endl << "------------------" << endl;
  for (auto person : pessoas) {
    Amigo *am = dynamic_cast<Amigo *>(person);
    if (am != nullptr) {
      cout << am->getBday() << " : " << am->getName() << endl;
    }
  }
  cout << "------------------" << endl;
}

void Agenda::imprimeEmail() const {
  cout << endl << "Emails:" << endl << "------------------" << endl;
  for (auto person : pessoas) {
    Conhecido *co = dynamic_cast<Conhecido *>(person);
    if (co != nullptr) {
      cout << co->getEmail() << " : " << co->getName() << endl;
    }
  }
  cout << "------------------" << endl;
}

#endif