#ifndef PESSOA_H
#define PESSOA_H
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class Pessoa {
 private:
  string nome;
  int idade;

 public:
  Pessoa() : nome("Indefinido"), idade(0){};
  Pessoa(string t_nome, int t_idade) : nome(t_nome), idade(t_idade){};
  string getName() const { return nome; }
  int getAge() const { return idade; }
  void set(string &t_nome, int &t_idade) {
    nome = t_nome;
    idade = t_idade;
  }
  virtual void addInformacoes() = 0;
  void addInformacoes_();
  virtual ~Pessoa() { cout << "Deleted " << nome << endl; };
};

inline void Pessoa::addInformacoes_() {
  string name;
  string age_s;
  int age;
  cout << "Insira o nome da pessoa: ";
  getline(cin, name);
  cout << "Insira a idade de " << name << ": ";
  getline(cin, age_s);
  istringstream stream(age_s);
  stream >> age;
  this->set(name, age);
  addInformacoes();
}

class Amigo : public Pessoa {
 private:
  string birthday;

 public:
  Amigo() : birthday("Indefinido"){};
  string getBday() const { return birthday; }
  void setBday(string &bday) { birthday = bday; }
  void addInformacoes() {
    string bday;
    cout << "Insira a data de aniversario de " << Pessoa::getName() << ": ";
    getline(cin, bday);
    setBday(bday);
  };
};

class Conhecido : public Pessoa {
 private:
  string email;

 public:
  Conhecido() : email("Indefinido"){};
  string getEmail() const { return email; }
  void setEmail(string &mail) { email = mail; }
  void addInformacoes() {
    string mail;
    cout << "Insira o E-mail de " << Pessoa::getName() << ": ";
    getline(cin, mail);
    setEmail(mail);
  };
};

#endif